#include "VideoCardStatusWindow.h"

#include <bitset>
#include <imgui/imgui.h>
#include "../core/Machine.h"
#include "../core/Cga.h"

void VideoCardStatusWindow::show(bool* open) {

    // ReSharper disable once CppDFAConstantConditions
    if (!_machine) {
        ImGui::Begin("Video Card Status", open);
        ImGui::Text("No Machine instance");
        ImGui::End();
        return;
    }

    // ReSharper disable once CppDFAUnreachableCode
    auto* cga = _machine->getBus()->cga();
    if (!cga) {
        ImGui::Begin("Video Card Status", open);
        ImGui::Text("CGA not present");
        ImGui::End();
        return;
    }

    // The window should present a simple table of CRTC registers (0..16)
    ImGui::Begin("Video Card Status", open);

    auto cga_state = cga->getDebugState();

    ImGui::Text("CGA Registers");
    ImGui::Separator();
    ImGui::Columns(2, nullptr, false);
    ImGui::Text("Mode Register:");
    ImGui::NextColumn();
    ImGui::Text("%s", std::bitset<8>(cga_state.mode_byte).to_string().c_str());
    // Show individual decoded mode bits in a table
    if (ImGui::BeginTable("cga_mode_flags", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit)) {
        ImGui::TableSetupColumn("Flag");
        ImGui::TableSetupColumn("V");
        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("Hi-res Text");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_hires_text ? "1" : "0");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("Graphics Mode");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_graphics ? "1" : "0");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("B/W Palette");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_bw ? "1" : "0");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("Display Enable");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_enable ? "1" : "0");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("Hi-res Graphics");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_hires_gfx ? "1" : "0");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("Blinking Enabled");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(cga_state.mode_blinking ? "1" : "0");

        ImGui::EndTable();
    }
    ImGui::NextColumn();

    ImGui::Separator();

    ImGui::Text("Clock Divisor:");
    ImGui::NextColumn();
    ImGui::Text("%d", cga_state.clock_divisor);
    ImGui::NextColumn();

    // Show frame/tick stats and derived refresh rate
    ImGui::Columns(2, nullptr, false);
    ImGui::Separator();
    ImGui::Text("Frame Count:");
    ImGui::NextColumn();
    ImGui::Text("%llu", static_cast<unsigned long long>(cga_state.frame_count));
    ImGui::NextColumn();
    ImGui::Text("Ticks:");
    ImGui::NextColumn();
    ImGui::Text("%llu", static_cast<unsigned long long>(cga_state.ticks));
    ImGui::Columns(1, nullptr, false);

    // Assume CGA ticks correspond to system crystal (14.31818 MHz) for refresh estimate.
    constexpr double CGA_CRYSTAL_HZ = 14318180.0;
    double avg_refresh_hz = 0.0;
    if (cga_state.frame_count > 0 && cga_state.ticks > 0) {
        avg_refresh_hz = (static_cast<double>(cga_state.frame_count) * CGA_CRYSTAL_HZ) /
            static_cast<double>(cga_state.ticks);
    }

    // Instantaneous (delta) refresh calculation to react quickly to changes.
    if (_prev_frame_count != 0 && _prev_ticks != 0 && cga_state.frame_count > _prev_frame_count && cga_state.ticks >
        _prev_ticks) {
        uint64_t frame_delta = cga_state.frame_count - _prev_frame_count;
        uint64_t tick_delta = cga_state.ticks - _prev_ticks;
        if (tick_delta > 0) {
            _instant_refresh_hz = (static_cast<double>(frame_delta) * CGA_CRYSTAL_HZ) / static_cast<double>(tick_delta);
        }
    }
    _prev_frame_count = cga_state.frame_count;
    _prev_ticks = cga_state.ticks;

    ImGui::Separator();
    ImGui::Text("Avg Refresh Rate: %.2f Hz", avg_refresh_hz);

    ImGui::Text("CRTC Registers");
    ImGui::Separator();
    if (const Crtc6845* crtc = cga->crtc()) {
        const auto& regs = crtc->get_registers();
        ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg;
        if (ImGui::BeginTable("crtc_regs", 3, flags)) {
            ImGui::TableSetupColumn("Reg");
            ImGui::TableSetupColumn("Hex");
            ImGui::TableSetupColumn("Dec");
            ImGui::TableHeadersRow();
            for (int i = 0; i < regs.size(); ++i) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%02X %s", i, cga->getRegisterName(i).c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%02X", regs[i]);
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%d", regs[i]);
            }
            ImGui::EndTable();
        }
    }
    else {
        ImGui::Text("Failed to get CRTC instance");
    }

    ImGui::End();
}
