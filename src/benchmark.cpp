// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#include "benchmark.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <memory>
#include <streambuf>

#include <SDL3/SDL_timer.h>

#include "core/Machine.h"

namespace {

// Discard routine core/device logging while measuring, without hiding stderr errors.
class BenchmarkOutputSilencer : public std::streambuf
{
public:
    BenchmarkOutputSilencer() : previous_buffer_(std::cout.rdbuf(this)) {}
    ~BenchmarkOutputSilencer() override { std::cout.rdbuf(previous_buffer_); }

protected:
    int_type overflow(const int_type ch) override { return traits_type::not_eof(ch); }
    std::streamsize xsputn(const char*, const std::streamsize count) override { return count; }

private:
    std::streambuf* previous_buffer_;
};

} // namespace

SDL_AppResult runBenchmark() {
    constexpr double kCpuHz = 14318180.0 / 3.0;
    constexpr double kMaxVirtualSeconds = 120.0;
    constexpr auto max_cycles = static_cast<uint64_t>(kCpuHz * kMaxVirtualSeconds);

    std::unique_ptr<Machine> machine;
    double elapsed_seconds = 0.0;
    {
        BenchmarkOutputSilencer silence;
        machine = std::make_unique<Machine>();
        machine->getCpu()->setSoftwareInterruptBreakpoint(0x19);
        machine->run();

        // Exclude initialization. Run the complete emulated machine without host
        // rendering, audio output, or wall-clock pacing until BIOS invokes INT 19h.
        const Uint64 frequency = SDL_GetPerformanceFrequency();
        const Uint64 start = SDL_GetPerformanceCounter();
        while (machine->isRunning() && machine->cycleCount() < max_cycles) {
            constexpr uint64_t kSliceCycles = 10000;
            const uint64_t cycles = std::min(kSliceCycles, max_cycles - machine->cycleCount());
            machine->run_for(cycles * 3);
        }
        elapsed_seconds = static_cast<double>(SDL_GetPerformanceCounter() - start) / frequency;
    }

    const bool reached_bootstrap = machine->breakpointHit();
    const uint64_t cycles = machine->cycleCount();
    const uint64_t instructions = machine->getCpu()->instructionCount();
    const uint64_t frames = machine->getBus()->cga()->getDebugState().frame_count;
    const double virtual_seconds = static_cast<double>(cycles) / kCpuHz;
    const double cycles_per_second = elapsed_seconds > 0.0 ? cycles / elapsed_seconds : 0.0;
    const double instructions_per_second = elapsed_seconds > 0.0 ? instructions / elapsed_seconds : 0.0;

    std::printf("XTCE-Blue benchmark: %s\n",
                reached_bootstrap ? "reached BIOS bootstrap (INT 19h)" : "stopped before BIOS bootstrap");
    std::printf("  Wall time:         %.6f s\n", elapsed_seconds);
    std::printf("  Emulated time:     %.6f s\n", virtual_seconds);
    std::printf("  CPU cycles:        %llu\n", static_cast<unsigned long long>(cycles));
    std::printf("  Instructions:      %llu\n", static_cast<unsigned long long>(instructions));
    std::printf("  Effective clock:   %.3f MHz\n", cycles_per_second / 1e6);
    std::printf("  Cycles/sec (CPS):   %.0f\n", cycles_per_second);
    std::printf("  Instructions/sec:  %.0f (%.3f MIPS)\n", instructions_per_second, instructions_per_second / 1e6);
    std::printf("  Cycles/instruction: %.3f\n", instructions > 0 ? static_cast<double>(cycles) / instructions : 0.0);
    std::printf("  Realtime speed:    %.3fx\n", cycles_per_second / kCpuHz);
    std::printf("  CGA frames:        %llu\n", static_cast<unsigned long long>(frames));

    if (!reached_bootstrap) {
        if (cycles >= max_cycles) {
            std::fprintf(stderr, "Benchmark timed out after %.0f seconds of emulated time.\n", kMaxVirtualSeconds);
        }
        else {
            std::fprintf(stderr, "CPU stopped before INT 19h (%s).\n", machine->getStateString().c_str());
        }
        return SDL_APP_FAILURE;
    }
    return SDL_APP_SUCCESS;
}
