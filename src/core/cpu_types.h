// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#ifndef XTCE_BLUE_CPU_TYPES_H
#define XTCE_BLUE_CPU_TYPES_H

// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdint>

enum class Register : std::size_t
{
    ES,
    CS,
    SS,
    DS,
    PC,
    IND,
    OPR,
    R7,
    R8,
    R9,
    R10,
    R11,
    TMPA,
    TMPB,
    TMPC,
    FLAGS,
    R16,
    R17,
    M,
    R,
    SIGMA,
    ONES,
    R22,
    R23,
    AX,
    CX,
    DX,
    BX,
    SP,
    BP,
    SI,
    DI,
};

constexpr std::size_t reg_to_idx(Register r) { return static_cast<std::size_t>(r); }

enum class QueueReadState
{
    NoOperation,
    FirstByte,
    Flush,
    SubsequentByte,
};

// Signals for one completed CPU clock, sampled before advancing the BIU phase.
// Status values use the physical S2:S0 and S4:S3 encodings, not MOO encodings.
struct CpuBusCycle
{
    enum class Phase : std::uint8_t
    {
        Idle,
        T1,
        T2,
        T3,
        T4,
        Wait
    };
    Phase phase = Phase::Idle;
    bool ale = false;
    std::uint32_t address = 0; // latched address; valid for comparison when ALE is asserted
    std::uint8_t bus_status = 7;
    std::uint8_t segment_status = 4; // 4 means no segment status in this phase
    std::uint8_t memory_status = 0; // asserted MRDC, AMWC, MWTC, in bits 2, 1, 0
    std::uint8_t io_status = 0; // asserted IORC, AIOWC, IOWC, in bits 2, 1, 0
    bool data_valid = false;
    std::uint8_t data = 0;
    QueueReadState queue_status = QueueReadState::NoOperation;
    std::uint8_t queue_byte = 0;
};


#endif // XTCE_BLUE_CPU_TYPES_H
