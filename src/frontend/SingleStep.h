// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <cstddef>

#include "../core/cpu_types.h"

struct SingleStepResult
{
    int cycles;
    bool completed;
    int instruction_cycles;
};

// Run a single test instruction.
// Stop on the first-byte queue status after all bytes of the test instruction
// have been consumed. Prefixes also produce first-byte statuses, so counting
// instruction bytes avoids stopping at the opcode that follows a prefix.
template <typename CpuType, typename Observer>
SingleStepResult runSingleStepObserved(CpuType& cpu, const std::size_t instruction_bytes, Observer&& observe,
                                       const int max_cycles = 1000000) {
    std::size_t bytes_read = 0;
    int instruction_cycles = 0;
    bool started = false;

    for (int cycles = 1; cycles <= max_cycles; ++cycles) {
        cpu.run_for(1);
        const QueueReadState status = cpu.getQueueStatus();

        if (status == QueueReadState::FirstByte && bytes_read >= instruction_bytes) {
            return {.cycles = cycles, .completed = true, .instruction_cycles = instruction_cycles};
        }

        if (status == QueueReadState::FirstByte) {
            started = true;
        }

        if (started) {
            observe(instruction_cycles++);
        }

        if (status == QueueReadState::FirstByte || status == QueueReadState::SubsequentByte) {
            ++bytes_read;
        }
    }
    return {.cycles = max_cycles, .completed = false, .instruction_cycles = instruction_cycles};
}

template <typename CpuType>
SingleStepResult runSingleStep(CpuType& cpu, std::size_t instruction_bytes, int max_cycles = 1000000) {
    return runSingleStepObserved(cpu, instruction_bytes, [](int) {}, max_cycles);
}
