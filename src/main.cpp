// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <mutex>
#include <string_view>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Blip_Buffer.h"

#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_sdlrenderer3.h>
#include <imgui/imgui.h>

#include "CLI11.hpp"
#include "benchmark.h"
#include "xtce_blue.h"

#include "gui/CpuStatusWindow.h"
#include "gui/CycleLogWindow.h"
#include "gui/DebuggerManager.h"
#include "gui/DebuggerWindow.h"
#include "gui/DisassemblyWindow.h"
#include "gui/DisplayDebugWindow.h"
#include "gui/DmacStatusWindow.h"
#include "gui/MemoryViewerWindow.h"
#include "gui/PicStatusWindow.h"
#include "gui/StackViewerWindow.h"
#include "gui/VideoCardStatusWindow.h"
#include "gui/imgui_memory_editor.h"

#include "core/Machine.h"

#include "frontend/DisplayRenderer.h"
#include "frontend/EmulationClock.h"
#include "frontend/TestRunner.h"
#include "frontend/keyboard.h"
#include "gui/InstructionHistoryWindow.h"

// Forward declare the callback we'll register with SDL_ShowOpenFileDialog
static void FileDialogCallback(void* userdata, const char* const* filelist, int filter_index);

// Default window size (TODO: Read from config)
constexpr uint32_t windowStartWidth = 1280;
constexpr uint32_t windowStartHeight = 1024;

bool init_audio(SDL_AudioDeviceID* outAudioDevice, MIX_Mixer** outMixer, SDL_AudioStream** outStream);

struct Config
{
    bool benchmark{false};
    std::string test_path{};
    size_t test_max{0};
    // Expect two-digit hex strings like "00".."FF"
    std::string opcode_start{"00"};
    std::string opcode_end{"FF"};
};

// Main application context. Holds SDL objects, Machine instance, and UI state.
struct AppContext
{
    Config config{};

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_AudioDeviceID audio_device = 0;
    MIX_Mixer* mixer = nullptr;
    SDL_AudioStream* pc_speaker_stream = nullptr;
    SDL_AppResult app_quit = SDL_APP_CONTINUE;
    Machine* machine = nullptr;
    DebuggerManager dbg_manager;
    bool running{true};

    // Blip buffer for audio
    Blip_Buffer blip_buf{};
    Blip_Synth<blip_high_quality, 1> blip_synth;
    blip_sample_t samples[BLIP_SAMPLE_COUNT];

    // FPS tracking
    Uint64 counter_frequency{SDL_GetPerformanceFrequency()};
    Uint64 last_counter{0};
    double fps_timer{0.0};
    int frame_count{0};
    float fps{0.0f};
    uint64_t virtual_frame_count{0};
    double virtual_refresh_hz{0.0};

    // Active emulation work and virtual time advanced during the title interval.
    Uint64 utilization_counter_ticks{0};
    uint64_t utilization_cycles{0};

    // Emulated time follows the wall clock, independently of presentation.
    double crystal_hz{14318180.0}; // 14.31818 MHz
    EmulationClock cpu_clock{crystal_hz / 3.0, counter_frequency};
    bool emulation_running{false};
    double audio_rate_ratio{1.0};

    // Display renderer and texture
    DisplayRenderer display_renderer;
    SDL_Texture* display_texture{nullptr};
    bool display_texture_dirty{true};
    uint64_t uploaded_cga_frame{0};
    uint64_t last_cga_ticks{0};
    uint8_t uploaded_cga_mode{0};
    uint8_t uploaded_cga_border{0};

    bool show_about{false};
    bool show_demo{false};
    bool show_io_debug{false};

    // Emulator Debugger flags.
    MemoryEditor mem_editor;
    bool show_memory_viewer{false};
    bool show_vram_viewer{false};
    bool show_stack_viewer{false};
    bool show_instruction_history{false};
    bool show_cpu_viewer{false};
    bool show_video_card_viewer{false};
    bool show_pic_viewer{false};
    bool show_dma_viewer{false};
    bool show_display_debug{false};
    bool cpu_running{true};
    bool show_disassembly{false};
    bool display_composite{false}; // composite rendering enabled flag

    // CPU timing display
    uint64_t last_cycle_count{0};
    double effective_mhz{0.0};

    // Cycle log UI
    bool show_cycle_log{false};
    bool cycle_log_auto_scroll{true};
    int cycle_log_capacity_ui{10000};
    size_t last_seen_cycle_log_size{0};

    // File dialog pending result handling
    std::mutex file_dialog_mutex;
    SDL_DialogFileFilter* pending_filters{nullptr}; // owned until dialog callback
    std::string pending_disk_path;
    bool pending_disk_load_flag{false};

    void resetUtilization() {
        utilization_counter_ticks = 0;
        utilization_cycles = 0;
    }

    int utilizationPercent() const {
        if (utilization_cycles == 0) {
            return 0;
        }
        const double execution_seconds = static_cast<double>(utilization_counter_ticks) / counter_frequency;
        const double virtual_seconds = static_cast<double>(utilization_cycles) / (crystal_hz / 3.0);
        // Truncate so 100% is reserved for work that reaches or exceeds its budget.
        return static_cast<int>(std::clamp(100.0 * execution_seconds / virtual_seconds, 0.0, 100.0));
    }

    void resetAudio() {
        SDL_ClearAudioStream(pc_speaker_stream);
        blip_buf.clear();
        // Clearing the buffer does not clear the synth's remembered amplitude.
        blip_synth.output(&blip_buf);
        machine->getElapsedPitTicks(true);
        blip_synth.update(0, machine->getBus()->speakerLevel() ? 1 : 0);
        audio_rate_ratio = 1.0;
        SDL_SetAudioStreamFrequencyRatio(pc_speaker_stream, 1.0f);
    }

    void resetMachine() {
        machine->resetMachine();
        last_cycle_count = machine->cycleCount();
        cpu_clock.reset(SDL_GetPerformanceCounter(), last_cycle_count, machine->isRunning());
        effective_mhz = 0.0;
        resetUtilization();
        display_texture_dirty = true;
        resetAudio();
    }

    void advanceEmulation(const Uint64 now, const double elapsed_seconds) {
        const uint64_t cycles_before = machine->cycleCount();
        const bool is_running = machine->isRunning();
        if (cycles_before < last_cycle_count) {
            // Includes resets made directly from the debugger window.
            cpu_clock.reset(now, cycles_before, is_running);
            resetUtilization();
            display_texture_dirty = true;
            resetAudio();
        }
        if (is_running != emulation_running) {
            resetUtilization();
            resetAudio();
        }

        // Small resampling corrections absorb drift in the audio device clock.
        // Audio buffering should never change how many CPU cycles are due.
        constexpr int bytes_per_second = AUDIO_SAMPLE_RATE * sizeof(int16_t);
        constexpr int max_queued_bytes = bytes_per_second * AUDIO_MAX_LATENCY_MS / 1000;
        int queued_bytes = SDL_GetAudioStreamQueued(pc_speaker_stream);

        if (queued_bytes > max_queued_bytes) {
            SDL_ClearAudioStream(pc_speaker_stream);
            queued_bytes = 0;
        }

        if (is_running && queued_bytes >= 0) {
            constexpr double target_seconds = AUDIO_MAX_LATENCY_MS / 2000.0;
            const double queued_seconds = static_cast<double>(queued_bytes) / bytes_per_second;
            const double desired_ratio = std::clamp(1.0 + 0.1 * (queued_seconds - target_seconds), 0.995, 1.005);
            audio_rate_ratio += (desired_ratio - audio_rate_ratio) * std::min(elapsed_seconds * 4.0, 1.0);

            SDL_SetAudioStreamFrequencyRatio(pc_speaker_stream, static_cast<float>(audio_rate_ratio));
        }

        uint64_t remaining_cycles = cpu_clock.cyclesDue(now, cycles_before, is_running);
        // About 1 ms per slice keeps audio generation granular even after a stall.
        const auto max_slice_cycles = static_cast<uint64_t>(crystal_hz / 3.0 / 1000.0);

        // Time emulation and audio generation, independently of host presentation.
        const Uint64 emulation_start = SDL_GetPerformanceCounter();
        while (remaining_cycles > 0) {
            const uint64_t slice_cycles = std::min(remaining_cycles, max_slice_cycles);
            // Machine takes crystal ticks: convert whole CPU cycles exactly once.
            machine->run_for(slice_cycles * 3);
            remaining_cycles -= slice_cycles;

            const auto pit_ticks = machine->getElapsedPitTicks(true);
            blip_buf.end_frame(static_cast<blip_time_t>(pit_ticks));
            int16_t audio_samples[2048];
            for (;;) {
                const int count = blip_buf.read_samples(audio_samples, 2048);
                if (count <= 0) {
                    break;
                }
                const int bytes = count * sizeof(int16_t);
                if (SDL_GetAudioStreamQueued(pc_speaker_stream) + bytes > max_queued_bytes) {
                    // Drop stale audio after a stall or a non-consuming device;
                    // retain recent sound without holding up CPU or UI progress.
                    SDL_ClearAudioStream(pc_speaker_stream);
                }
                SDL_PutAudioStreamData(pc_speaker_stream, audio_samples, bytes);
            }
            if (!machine->isRunning()) {
                cpu_clock.reset(now, machine->cycleCount(), false);
                resetAudio();
                break;
            }
        }
        const Uint64 emulation_end = SDL_GetPerformanceCounter();

        const uint64_t cycles_after = machine->cycleCount();
        if (!machine->isRunning()) {
            // Includes breakpoints reached during this batch; stepping is not sampled.
            resetUtilization();
        }
        else if (cycles_after > cycles_before) {
            utilization_counter_ticks += emulation_end - emulation_start;
            // Actual progress also handles partial batches and capped catch-up budgets.
            utilization_cycles += cycles_after - cycles_before;
        }
        // Pair executed cycles with the SAME interval that produced the budget.
        // No smoothing: missed budgets and genuine slowdowns remain visible.
        effective_mhz =
            elapsed_seconds > 0.0 ? static_cast<double>(cycles_after - cycles_before) / elapsed_seconds / 1e6 : 0.0;
        last_cycle_count = cycles_after;
        emulation_running = machine->isRunning();
    }

    void updateDisplayTexture(CGA* cga) {
        const auto state = cga->getDebugState();
        const uint8_t border = cga->getOverscanColor();
        const bool reset = state.ticks < last_cga_ticks;
        last_cga_ticks = state.ticks;
        if (!display_texture_dirty && !reset && state.frame_count == uploaded_cga_frame &&
            (!display_composite || (state.mode_byte == uploaded_cga_mode && border == uploaded_cga_border))) {
            return;
        }

        display_renderer.render(cga);

        constexpr int row_bytes = DisplayRenderer::WIDTH * DisplayRenderer::BYTES_PER_PIXEL;
        void* tex_pixels = nullptr;
        int tex_pitch = 0;
        bool uploaded = false;

        if (SDL_LockTexture(display_texture, nullptr, &tex_pixels, &tex_pitch)) {
            const uint8_t* src = display_renderer.pixels();
            for (int y = 0; y < DisplayRenderer::HEIGHT; ++y) {
                auto* dst_row = static_cast<uint8_t*>(tex_pixels) + static_cast<size_t>(y) * tex_pitch;
                memcpy(dst_row, src + static_cast<size_t>(y) * row_bytes, row_bytes);
            }
            SDL_UnlockTexture(display_texture);
            uploaded = true;
        }
        else {
            uploaded = SDL_UpdateTexture(display_texture, nullptr, display_renderer.pixels(), row_bytes);
        }

        if (uploaded) {
            uploaded_cga_frame = state.frame_count;
            uploaded_cga_mode = state.mode_byte;
            uploaded_cga_border = border;
            display_texture_dirty = false;
        }
        else {
            display_texture_dirty = true;
            SDL_Log("CGA texture upload failed: %s", SDL_GetError());
        }
    }
};

// SDL failure callback - logs the error and returns failure code.
SDL_AppResult SDL_Fail() {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
    return SDL_APP_FAILURE;
}

// SDL Application Initialization callback. We do all our emulator initialization here.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {

    auto cfg = Config{};

    // Run CLI11 to parse command-line arguments
    CLI::App cli_app{std::format("{} v{}", APP_NAME, APP_VERSION)};
    argv = cli_app.ensure_utf8(argv);
    auto* benchmark_option =
        cli_app.add_flag("--benchmark", cfg.benchmark,
                         "Run headless and unthrottled until BIOS bootstrap (INT 19h), then print performance stats");

    // Create a subcommand 'run-tests' with options for test path and an optional max
    auto* run_test = cli_app.add_subcommand("run-tests", "Run SingleStepTests");
    run_test->excludes(benchmark_option);
    run_test->add_option("--test-path", cfg.test_path, "Path to location of SingleStepTests")->required(false);
    run_test->add_option("--test-max", cfg.test_max, "Maximum number of tests to run (0 = no limit)");
    run_test
        ->add_option(
            "--opcode-start", cfg.opcode_start,
            "Starting opcode prefix as two-digit hex (00..FF), matched against filename prefix e.g. '00.MOO.gz'")
        ->capture_default_str();
    run_test->add_option("--opcode-end", cfg.opcode_end, "Ending opcode prefix as two-digit hex (00..FF)")
        ->capture_default_str();

    // Parse the arguments (this is an expansion of the CLI11_PARSE macro)
    try {
        cli_app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        cli_app.exit(e);
        return SDL_APP_FAILURE;
    }

    if (cfg.benchmark) {
        return runBenchmark();
    }

    // If subcommand was invoked, run tests and exit
    if (*run_test) {
        // Parse and validate two-digit hex opcode range strings
        auto parse_hex_byte = [&](const std::string& s, int& out) -> bool
        {
            if (s.size() != 2)
                return false;
            if (!std::isxdigit(static_cast<unsigned char>(s[0])) || !std::isxdigit(static_cast<unsigned char>(s[1])))
                return false;
            try {
                out = std::stoi(s, nullptr, 16);
            }
            catch (...) {
                return false;
            }
            return out >= 0 && out <= 0xFF;
        };

        int startVal = 0;
        int endVal = 0xFF;
        if (!parse_hex_byte(cfg.opcode_start, startVal)) {
            std::cerr << "Error: --opcode-start must be a two-digit hex value (00..FF)\n";
            return SDL_APP_FAILURE;
        }
        if (!parse_hex_byte(cfg.opcode_end, endVal)) {
            std::cerr << "Error: --opcode-end must be a two-digit hex value (00..FF)\n";
            return SDL_APP_FAILURE;
        }
        if (startVal > endVal) {
            std::cerr << "Error: --opcode-start must be <= --opcode-end\n";
            return SDL_APP_FAILURE;
        }

        const auto test_runner = new TestRunner();
        if (!cfg.test_path.empty()) {
            const std::filesystem::path p(cfg.test_path);
            if (std::filesystem::is_directory(p)) {
                for (const auto& entry : std::filesystem::directory_iterator(p)) {
                    if (!entry.is_regular_file())
                        continue;
                    const auto name = entry.path().filename().string();
                    if (name.size() < 3)
                        continue;
                    // Expect filename starting with two hex digits followed by a dot, e.g. "00.MOO.gz"
                    if (!std::isxdigit(static_cast<unsigned char>(name[0])) ||
                        !std::isxdigit(static_cast<unsigned char>(name[1])) || name[2] != '.')
                        continue;
                    int val = 0;
                    try {
                        val = std::stoi(name.substr(0, 2), nullptr, 16);
                    }
                    catch (...) {
                        continue;
                    }
                    if (val >= startVal && val <= endVal) {
                        test_runner->addFiles(entry.path().string());
                    }
                }
            }
            else if (std::filesystem::is_regular_file(p)) {
                const auto name = p.filename().string();
                if (name.size() >= 3 && std::isxdigit(static_cast<unsigned char>(name[0])) &&
                    std::isxdigit(static_cast<unsigned char>(name[1])) && name[2] == '.') {
                    try {
                        const int val = std::stoi(name.substr(0, 2), nullptr, 16);
                        if (val >= startVal && val <= endVal)
                            test_runner->addFiles(p.string());
                    }
                    catch (...) {
                        /* ignore */
                    }
                }
            }
            test_runner->listFiles();
        }
        test_runner->runAllTests(cfg.test_max);
        return SDL_APP_SUCCESS;
    }


    // Initialize SDL with the services we need specified in flags. We want to use Video and Audio.
    if (not SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        return SDL_Fail();
    }

    // Initialize SDL TTF (unused at the moment...)
    if (not TTF_Init()) {
        return SDL_Fail();
    }

    // Create our main window. We want it to be resizable and high-DPI aware.
    SDL_Window* window = SDL_CreateWindow("XTCE-Blue", windowStartWidth, windowStartHeight,
                                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if (not window) {
        return SDL_Fail();
    }

    // If we want to show graphics, we need a renderer, so create one now.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (not renderer) {
        return SDL_Fail();
    }

    // Presentation is uncapped; the CPU has its own wall-clock deadlines.
    if (!SDL_SetRenderVSync(renderer, 0)) {
        SDL_Log("Could not disable presentation vsync: %s", SDL_GetError());
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Initialize ImGui's SDL3 integrations.
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Get the directory our executable ran from - we can use this base path for loading resources, etc.
    const auto basePathPtr = SDL_GetBasePath();
    if (not basePathPtr) {
        return SDL_Fail();
    }
    const std::filesystem::path basePath = basePathPtr;

    // const auto fontPath = basePath / "Inter-VariableFont.ttf";
    // TTF_Font* font = TTF_OpenFont(fontPath.string().c_str(), 36);
    // if (not font) {
    //     return SDL_Fail();
    // }
    //
    // // render the font to a surface
    // const std::string_view text = "Hello SDL!";
    // SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.data(), text.length(), { 255,255,255 });
    //
    // // make a texture from the surface
    // SDL_Texture* messageTex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    //
    // // we no longer need the font or the surface, so we can destroy those now.
    // TTF_CloseFont(font);
    // SDL_DestroySurface(surfaceMessage);

    // get the on-screen dimensions of the text. this is necessary for rendering it
    // auto messageTexProps = SDL_GetTextureProperties(messageTex);
    // SDL_FRect text_rect{
    //         .x = 0,
    //         .y = 0,
    //         .w = float(SDL_GetNumberProperty(messageTexProps, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0)),
    //         .h = float(SDL_GetNumberProperty(messageTexProps, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0))
    // };

    // Initialize audio
    SDL_AudioDeviceID audio_device;
    MIX_Mixer* mixer;
    SDL_AudioStream* stream;
    init_audio(&audio_device, &mixer, &stream);


    // Create a Machine - this represents our emulator core.
    auto machine = new Machine();

    // Set up our emulator application context.
    auto* ctx = new AppContext();
    ctx->window = window;
    ctx->renderer = renderer;
    ctx->audio_device = audio_device;
    ctx->mixer = mixer;
    ctx->pc_speaker_stream = stream;
    ctx->machine = machine;

    // Initialize Blip_Buffer
    ctx->blip_buf.sample_rate(AUDIO_SAMPLE_RATE);
    ctx->blip_buf.bass_freq(200); // 200Hz high-pass filter to reduce bass rumble
    // PIT clock is (crystal / 12) or ~ 1.19318 MHz
    ctx->blip_buf.clock_rate(static_cast<long>(ctx->crystal_hz / 12.0));
    ctx->blip_synth.volume(0.0175); // Preserve the gain previously divided by amplitude range 20.
    ctx->blip_synth.output(&ctx->blip_buf);

    const blip_eq_t eq(0.0, // 0dB = fairly flat highs
                       8000, // roll off above ~8kHz
                       AUDIO_SAMPLE_RATE);

    ctx->blip_synth.treble_eq(eq);

    // Attach our callback
    ctx->machine->getBus()->setSpeakerCallback(
        [ctx](uint64_t tick, const bool state, const bool enabled)
        {
            // Calculate elapsed ticks
            const auto elapsed_ticks = static_cast<blip_time_t>(ctx->machine->getElapsedPitTicks(false));
            ctx->blip_synth.update(elapsed_ticks, enabled && state ? 1 : 0);
        });

    // Show our new SDL window, and print some debugs about its size and DPI.
    SDL_ShowWindow(window);
    {
        int width, height, bbwidth, bbheight;
        SDL_GetWindowSize(window, &width, &height);
        SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
        SDL_Log("Window size: %ix%i", width, height);
        SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
        if (width != bbwidth) {
            SDL_Log("This is a highdpi environment.");
        }
    }

    // Create the display texture (full front buffer size); aperture will be applied as source rect when rendering.
    ctx->display_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                                             DisplayRenderer::WIDTH, DisplayRenderer::HEIGHT);
    if (!ctx->display_texture) {
        SDL_Log("Failed to create display texture: %s", SDL_GetError());
        // return SDL_APP_FAILURE;
    }

    // Register our various debug windows with the AppContext's dbgManager
    ctx->dbg_manager.addWindow("Disassembly", std::make_unique<DisassemblyWindow>(machine), &ctx->show_disassembly);
    ctx->dbg_manager.addWindow("Cpu Status", std::make_unique<CpuStatusWindow>(machine), &ctx->show_cpu_viewer);
    ctx->dbg_manager.addWindow("Memory Viewer", std::make_unique<MemoryViewerWindow>(machine),
                               &ctx->show_memory_viewer);
    ctx->dbg_manager.addWindow("VRAM Viewer", std::make_unique<MemoryViewerWindow>(machine, true),
                               &ctx->show_vram_viewer);
    ctx->dbg_manager.addWindow("Stack Viewer", std::make_unique<StackViewerWindow>(machine), &ctx->show_stack_viewer);
    ctx->dbg_manager.addWindow("Cycle Log", std::make_unique<CycleLogWindow>(machine), &ctx->show_cycle_log);
    ctx->dbg_manager.addWindow("Instruction History", std::make_unique<InstructionHistoryWindow>(machine),
                               &ctx->show_instruction_history);
    ctx->dbg_manager.addWindow("Video Card Status", std::make_unique<VideoCardStatusWindow>(machine),
                               &ctx->show_video_card_viewer);
    ctx->dbg_manager.addWindow("PIC Status", std::make_unique<PicStatusWindow>(machine), &ctx->show_pic_viewer);
    ctx->dbg_manager.addWindow("DMA Status", std::make_unique<DmacStatusWindow>(machine), &ctx->show_dma_viewer);
    // Display debug window uses the app's displayTexture pointer
    ctx->dbg_manager.addWindow("Display Debug", std::make_unique<DisplayDebugWindow>(&ctx->display_texture),
                               &ctx->show_display_debug);

    // Initialize cycle log UI capacity from machine state
    ctx->cycle_log_capacity_ui = static_cast<int>(ctx->machine->getCycleLogCapacity());

    // Assign our application state via the pointer passed in.
    *appstate = ctx;

    SDL_Log("Application started successfully!");

    // Start the emulator!
    ctx->machine->run();
    ctx->emulation_running = true;
    ctx->last_counter = SDL_GetPerformanceCounter();
    ctx->last_cycle_count = ctx->machine->cycleCount();
    ctx->cpu_clock.reset(ctx->last_counter, ctx->last_cycle_count, true);

    return SDL_APP_CONTINUE;
}

// SDL's event callback. Handle UI events and pass relevant input to the Machine.
// SDL_AppEvent_func requires a non-const event pointer, even though we only read it.
// ReSharper disable once CppParameterMayBeConstPtrOrRef
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) { // NOLINT(readability-non-const-parameter)
    auto* app = static_cast<AppContext*>(appstate);
    uint8_t sc{};

    // Let ImGui process the event first
    ImGui_ImplSDL3_ProcessEvent(event);
    // Get a ImGuiIO for input capture checks
    const ImGuiIO& io = ImGui::GetIO();

    switch (event->type) {
            // case SDL_EVENT_MOUSE_MOTION:
            //     SDL_Log("MOUSE MOTION: x=%f y=%f rel=(%f,%f)",
            //             event->motion.x, event->motion.y,
            //             event->motion.xrel, event->motion.yrel);
            //     break;
            //
            // case SDL_EVENT_MOUSE_BUTTON_DOWN:
            //     SDL_Log("MOUSE BUTTON DOWN: button=%d at (%f,%f)",
            //             event->button.button, event->button.x, event->button.y);
            //     break;
            //
            // case SDL_EVENT_MOUSE_BUTTON_UP:
            //     SDL_Log("MOUSE BUTTON UP: button=%d at (%f,%f)",
            //             event->button.button, event->button.x, event->button.y);
            //     break;
            //
            // case SDL_EVENT_MOUSE_WHEEL:
            //     SDL_Log("MOUSE WHEEL: x=%f y=%f", event->wheel.x, event->wheel.y);
            //     break;

        case SDL_EVENT_KEY_DOWN:
            // Only send key events to the machine if ImGui is not capturing keyboard input.
            if (!io.WantCaptureKeyboard) {
                sc = translate_SDL_key(event->key.key, true);
                app->machine->sendScanCode(sc);
            }
            break;

        case SDL_EVENT_KEY_UP:
            // Only send key events to the machine if ImGui is not capturing keyboard input.
            if (!io.WantCaptureKeyboard) {
                sc = translate_SDL_key(event->key.key, false);
                app->machine->sendScanCode(sc);
            }
            break;

        case SDL_EVENT_QUIT:
            SDL_Log("QUIT event");
            app->running = false;
            break;

        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

// Main SDL loop. This is called repeatedly to run our program - we do our emulation stepping and rendering here.
SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* app = static_cast<AppContext*>(appstate);
    if (!app || !app->machine) {
        return SDL_APP_FAILURE;
    }

    // Get the time delta since last update.
    const Uint64 now = SDL_GetPerformanceCounter();
    const double delta = static_cast<double>(now - app->last_counter) / static_cast<double>(app->counter_frequency);
    app->last_counter = now;

    // Include elapsed time even when this iteration skips rendering.
    app->fps_timer += delta;

    // Advance emulation and see if frames were emitted
    const auto virtual_frames_before = app->machine->getBus()->cga()->getDebugState().frame_count;
    app->advanceEmulation(now, delta);
    if (const auto virtual_frames_after = app->machine->getBus()->cga()->getDebugState().frame_count;
        virtual_frames_after >= virtual_frames_before) {
        app->virtual_frame_count += virtual_frames_after - virtual_frames_before;
    }

    // Set window title with perf stats
    if (app->fps_timer >= 0.5) {
        // Measure host presentations and completed CGA frames over the same wall-clock interval.
        app->fps = static_cast<float>(app->frame_count / app->fps_timer);
        app->virtual_refresh_hz = static_cast<double>(app->virtual_frame_count) / app->fps_timer;
        app->frame_count = 0;
        app->virtual_frame_count = 0;
        app->fps_timer = 0.0;

        const int utilization = app->utilizationPercent();
        app->resetUtilization();

        char title[128];
        snprintf(title, sizeof(title), "XTCE-Blue — %.1f FPS | CPU %.2f MHz | CGA %.1f Hz | %d%%", app->fps,
                 app->effective_mhz, app->virtual_refresh_hz, utilization);
        SDL_SetWindowTitle(app->window, title);
    }

    // If nothing to run, we still yield to UI and rendering below
    if (!app->running) {
        return SDL_APP_SUCCESS;
    }

    // Ensure no stale scaling state
    SDL_SetRenderViewport(app->renderer, nullptr);
    SDL_SetRenderClipRect(app->renderer, nullptr);

    // Start a new ImGui frame - SDL integrations first, native NewFrame() second.
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui::NewFrame();

    // Draw the main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Emulator")) {
            if (ImGui::MenuItem("About...")) {
                app->show_about = true; // open modal dialog
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                app->running = false; // signals to stop in next iteration
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Machine")) {
            if (ImGui::MenuItem("Reboot")) {
                app->resetMachine();
            }
            ImGui::EndMenu();
        }

        // Display menu for video output options
        if (ImGui::BeginMenu("Display")) {
            bool composite = app->display_composite;
            if (ImGui::MenuItem("Composite", nullptr, &composite)) {
                app->display_composite = composite;
                app->display_renderer.setComposite(composite);
                app->display_texture_dirty = true;
            }
            ImGui::EndMenu();
        }

        // Media menu for loading disk images
        if (ImGui::BeginMenu("Media")) {
            if (ImGui::MenuItem("Load floppy image")) {
                // Allocate filters on the heap; they must remain valid until the callback runs.
                auto filters = new SDL_DialogFileFilter[1];
                filters[0].name = "IMG files";
                filters[0].pattern = "img;ima;dsk;bin";

                // Store pointer so callback can free it
                {
                    std::lock_guard<std::mutex> lk(app->file_dialog_mutex);
                    app->pending_filters = filters;
                }

                // Launch asynchronous native open-file dialog. allow_many=false
                SDL_ShowOpenFileDialog(FileDialogCallback, app, app->window, filters, 1, nullptr, false);
            }
            ImGui::EndMenu();
        }

        // Debug menu contains development and inspection tools
        if (ImGui::BeginMenu("Debug")) {
            // Add debugger window items managed by DebuggerManager
            app->dbg_manager.drawMenuItems();

            // Dump submenu for quick binary dumps of emulator state
            if (ImGui::BeginMenu("Dump")) {
                if (ImGui::MenuItem("Dump memory")) {
                    if (app->machine) {
                        uint8_t* ram = app->machine->ram();
                        if (const size_t size = app->machine->ramSize(); !ram || size == 0) {
                            SDL_Log("Dump memory: RAM pointer null or size is 0");
                        }
                        else {
                            if (std::ofstream out("memdump.bin", std::ios::binary); !out) {
                                SDL_Log("Dump memory: Failed to open memdump.bin for writing: %s", SDL_GetError());
                            }
                            else {
                                out.write(reinterpret_cast<const char*>(ram), static_cast<std::streamsize>(size));
                                if (!out) {
                                    SDL_Log("Dump memory: Failed to write RAM to file");
                                }
                                else {
                                    out.flush();
                                    SDL_Log("Dump memory: Wrote %zu bytes to memdump.bin", size);
                                }
                            }
                        }
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (app->show_about) {
        if (ImGui::Begin("About XTCE-Blue", &app->show_about,
                         ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::Text("XTCE-Blue");
            ImGui::Separator();
            ImGui::Text("Version: 0.1.0");
            ImGui::Text("Authors:");
            ImGui::BulletText("Andrew Jenner (reenigne) - original XTCE CPU core");
            ImGui::BulletText("Daniel Balsom (gloriouscow) - SDL3 frontend, CGA implementation");

            ImGui::NewLine();
            ImGui::TextWrapped("XTCE-Blue is a cycle-accurate IBM XT emulator written in C++ using SDL3 and ImGui. "
                               "XTCE-Blue's 8088 emulation is powered by the XTCE 8088 CPU core - "
                               "which emulates the 8088 at the microcode level.");

            ImGui::NewLine();
            if (ImGui::Button("OK", ImVec2(120, 0))) {
                app->show_about = false;
            }
        }
        ImGui::End();
    }

    if (app->show_demo) {
        ImGui::ShowDemoWindow();
    }

    if (app->show_io_debug) {
        const ImVec2 p = ImGui::GetMousePos();
        const ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Input debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("ImGui::GetIO: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
        ImGui::Text("ImGui::GetMousePos(): (%.1f, %.1f)", p.x, p.y);
        ImGui::Text("WantCaptureMouse: %s", io.WantCaptureMouse ? "true" : "false");
        ImGui::End();
    }

    // Memory viewers are registered into DebuggerManager and will be drawn via dbgManager.showAll().
    // (No manual DrawWindow call here to avoid duplicate windows/menu items.)

    // Show any registered debug windows
    app->dbg_manager.showAll();

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    ImGui::Render();

    // Update and render display texture (CGA) before ImGui is drawn so UI overlays appear on top.
    if (app->display_texture && app->machine) {
        if (auto* bus = app->machine->getBus()) {
            if (auto* cga = bus->cga()) {
                app->updateDisplayTexture(cga);
                const auto aperture = CGA::getDisplayAperture();
                SDL_Rect src_rect_i{.x = static_cast<int>(aperture.x),
                                    .y = static_cast<int>(aperture.y),
                                    .w = static_cast<int>(aperture.w),
                                    .h = static_cast<int>(aperture.h)};
                SDL_FRect src_rect_f{.x = static_cast<float>(src_rect_i.x),
                                     .y = static_cast<float>(src_rect_i.y),
                                     .w = static_cast<float>(src_rect_i.w),
                                     .h = static_cast<float>(src_rect_i.h)};
                SDL_Rect dst;
                int ww, wh;
                SDL_GetWindowSize(app->window, &ww, &wh);
                dst.x = 0;
                dst.y = 0;
                dst.w = ww;
                dst.h = wh;
                SDL_FRect dstF{.x = 0.0f, .y = 0.0f, .w = static_cast<float>(ww), .h = static_cast<float>(wh)};
                if (!SDL_RenderTexture(app->renderer, app->display_texture, &src_rect_f, &dstF)) {
                    SDL_Log("SDL_RenderTexture failed: %s", SDL_GetError());
                    SDL_SetRenderDrawColor(app->renderer, 0xFF, 0x00, 0xFF, 0xFF);
                    SDL_RenderFillRect(app->renderer, &dstF);
                    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
                }
            }
        }
    }

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), app->renderer);
    if (SDL_RenderPresent(app->renderer)) {
        app->frame_count++;
    }

    // Process pending file dialog result (if any)
    {
        std::lock_guard<std::mutex> lk(app->file_dialog_mutex);
        if (app->pending_disk_load_flag) {
            app->pending_disk_load_flag = false;

            // Load the selected disk image into the emulator
            if (auto* bus = app->machine->getBus()) {
                try {
                    if (std::ifstream in(app->pending_disk_path, std::ios::binary); !in) {
                        SDL_Log("Failed to open selected floppy image: %s", app->pending_disk_path.c_str());
                    }
                    else {
                        std::vector<uint8_t> data((std::istreambuf_iterator<char>(in)),
                                                  std::istreambuf_iterator<char>());
                        bus->fdc()->loadDisk(0, data, true);
                        SDL_Log("Loaded floppy image '%s' into FDC drive 0 (%zu bytes)", app->pending_disk_path.c_str(),
                                data.size());
                    }
                }
                catch (const std::exception& e) {
                    SDL_Log("Exception while loading floppy image: %s", e.what());
                }
            }
        }
    }

    return app->app_quit;
}

// Called when our SDL app needs to exit. We should clean up all our resources here.
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    // Command-line modes return from initialization without creating an SDL app.
    if (!appstate) {
        return;
    }
    if (const auto* app = static_cast<AppContext*>(appstate)) {
        if (app->display_texture) {
            SDL_DestroyTexture(app->display_texture);
        }
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);

        MIX_DestroyMixer(app->mixer);
        SDL_CloseAudioDevice(app->audio_device);

        delete app;
    }

    TTF_Quit();
    MIX_Quit();

    SDL_Log("Application quit successfully!");
    SDL_Quit();
}

bool init_audio(SDL_AudioDeviceID* outAudioDevice, MIX_Mixer** outMixer, SDL_AudioStream** outStream) {

    SDL_SetHint(SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES, "512");

    // Desired audio spec
    constexpr auto out_spec = SDL_AudioSpec{
        .format = SDL_AUDIO_S16,
        .channels = 2,
        .freq = AUDIO_SAMPLE_RATE,
    };

    // 1) Init SDL audio
    const SDL_AudioDeviceID audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &out_spec);
    if (not audio_device) {
        SDL_Log("Failed to open audio device: %s", SDL_GetError());
        return false;
    }

    // 2) Init SDL_mixer
    if (not MIX_Init()) {
        // returns bool in SDL3_mixer
        SDL_Log("MIX_Init failed: %s", SDL_GetError());
        return false;
    }

    // 3) Create a mixer bound to the default playback device.
    MIX_Mixer* mixer = MIX_CreateMixerDevice(audio_device, &out_spec);
    if (not mixer) {
        SDL_Log("Mix_OpenAudioDevice failed: %s", SDL_GetError());
        SDL_CloseAudioDevice(audio_device);
        return false;
    }

    SDL_Log("Audio initialized successfully (device %u)", audio_device);

    // 4) Create an audio stream
    // Create an Audio stream for the PC speaker.
    constexpr auto in_spec = SDL_AudioSpec{
        .format = SDL_AUDIO_S16,
        .channels = 1,
        .freq = AUDIO_SAMPLE_RATE,
    };
    SDL_AudioStream* stream = SDL_CreateAudioStream(&in_spec, &out_spec);
    if (not stream) {
        SDL_Log("SDL_CreateAudioStream failed: %s", SDL_GetError());
        MIX_DestroyMixer(mixer);
        SDL_CloseAudioDevice(audio_device);
        return false;
    }

    SDL_BindAudioStream(audio_device, stream);
    SDL_ResumeAudioDevice(audio_device);
    *outAudioDevice = audio_device;
    *outMixer = mixer;
    *outStream = stream;

    return true;
}

// Callback invoked by SDL when the open-file dialog completes. It may be called on another thread.
static void FileDialogCallback(void* userdata, const char* const* filelist, int /*filter_index*/) {
    if (!userdata) {
        return;
    }
    auto* app = static_cast<AppContext*>(userdata);
    if (!filelist) {
        SDL_Log("File dialog error: %s", SDL_GetError());
    }
    else if (!filelist[0]) {
        SDL_Log("File dialog canceled by user.");
    }
    else {
        // Store the first selected path for processing on the main thread
        {
            const char* path = filelist[0];
            std::lock_guard<std::mutex> lk(app->file_dialog_mutex);
            app->pending_disk_path = path;
            app->pending_disk_load_flag = true;
        }
    }

    // Free any filters array we allocated earlier and stored in the context
    if (app->pending_filters) {
        delete[] app->pending_filters;
        app->pending_filters = nullptr;
    }
}
