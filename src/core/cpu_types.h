// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#ifndef XTCE_BLUE_CPU_TYPES_H
#define XTCE_BLUE_CPU_TYPES_H

// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdint>

// Physical S2:S0 bus-status encoding, shared by CPU, bus and logging code.
enum class BusStatus : std::uint8_t
{
    InterruptAcknowledge = 0,
    IoRead = 1,
    IoWrite = 2,
    Halt = 3,
    InstructionFetch = 4,
    MemoryRead = 5,
    MemoryWrite = 6,
    Passive = 7,
};

// CPU bus-cycle states.
enum class TState : std::uint8_t
{
    TIdle = 0,
    T1 = 1,
    T2 = 2,
    T3 = 3,
    T4 = 4,
    TWait = 5,
};

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
    TState phase = TState::TIdle;
    bool ale = false;
    bool bhe = false; // Active-low upper-byte enable, used by V30/8086 hosts.
    std::uint32_t address = 0; // latched address; valid for comparison when ALE is asserted
    std::uint8_t bus_status = static_cast<std::uint8_t>(BusStatus::Passive);
    std::uint8_t segment_status = 4; // 4 means no segment status in this phase
    std::uint8_t memory_status = 0; // asserted MRDC, AMWC, MWTC, in bits 2, 1, 0
    std::uint8_t io_status = 0; // asserted IORC, AIOWC, IOWC, in bits 2, 1, 0
    bool data_valid = false;
    std::uint16_t data = 0;
    QueueReadState queue_status = QueueReadState::NoOperation;
    std::uint8_t queue_byte = 0;
};


#endif // XTCE_BLUE_CPU_TYPES_H
