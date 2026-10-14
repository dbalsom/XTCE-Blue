// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <algorithm>
#include <format>
#include <span>
#include <string>

#include "../core/cpu_types.h"
#include "../moo/mooreader.h"
#include "../core/test_support/FlatBus.h"

inline std::string compareSstAccesses(const std::span<const Moo::Reader::Cycle> cycles,
    const std::span<const marty::testing::BusAccess> actual, bool word_bus) {
    std::vector<marty::testing::BusAccess> expected;
    uint32_t address = 0;
    uint8_t status = 7;
    bool high_enabled = false;
    for (const auto& cycle : cycles) {
        if (cycle.pin_bitfield0.ale) {
            address = cycle.address_latch;
            status = cycle.bus_status;
            high_enabled = !cycle.pin_bitfield1.bhe;
        }
        if (cycle.t_state == 3 && status >= 1 && status <= 4) {
            const bool port = status <= 2;
            const bool write = status == 2 || status == 4;
            const unsigned lanes = word_bus && !(address & 1) && high_enabled ? 2 : 1;
            const unsigned shift = word_bus && (address & 1) ? 8 : 0;
            for (unsigned lane = 0; lane < lanes; ++lane) {
                expected.push_back({(address + lane) & (port ? 0xffffu : 0xfffffu),
                    uint8_t(cycle.data_bus >> (shift + lane * 8)), write, port});
            }
        }
    }
    if (actual.size() != expected.size()) {
        return std::format("Operand/I/O access count: expected {}, got {}", expected.size(), actual.size());
    }
    for (size_t n = 0; n < actual.size(); ++n) {
        const auto& a = actual[n];
        const auto& e = expected[n];
        if (a.address != e.address || a.value != e.value || a.write != e.write || a.port != e.port) {
            return std::format("Operand/I/O access {}: expected {} {} {:05X}={:02X}, got {} {} {:05X}={:02X}",
                n, e.port ? "I/O" : "RAM", e.write ? "write" : "read", e.address, e.value,
                a.port ? "I/O" : "RAM", a.write ? "write" : "read", a.address, a.value);
        }
    }
    return {};
}

inline bool matchesSstRegister(const Moo::Reader::Test& test, const Moo::REG16 reg, const uint16_t actual) {
    const uint16_t expected = test.GetFinalRegister(reg, false);
    // SST captures the hardware's undefined flags too. Always compare the full
    // FLAGS word, even when the file supplies a mask for undefined bits.
    const uint16_t mask = reg != Moo::REG16::FLAGS && test.final_state.masks.HasRegister(reg)
        ? test.final_state.masks.GetRegister(reg) : 0xffff;
    return ((actual ^ expected) & mask) == 0;
}

struct SstTraceComparison {
    std::string timing;
    std::string bus;
    std::string queue;
};

// Compare captured CpuBusCycles to Moo cycles
inline SstTraceComparison compareSstTrace(const std::span<const Moo::Reader::Cycle> expected,
                                          const std::span<const CpuBusCycle> actual, bool word_bus = false) {
    SstTraceComparison result;

    if (expected.size() != actual.size()) {
        result.timing = std::format("Cycle count: expected {}, got {}", expected.size(), actual.size());
    }

    for (size_t i = 0; i < std::min(expected.size(), actual.size()); ++i) {
        const auto& e = expected[i];
        const auto& a = actual[i];

        auto check = [i](std::string& message, const char* field, unsigned want, unsigned got) {
            if (want != got && message.empty()) {
                message = std::format("Cycle {} {}: expected {:#x}, got {:#x}", i, field, want, got);
            }
        };

        check(result.timing, "T-state", e.t_state, static_cast<unsigned>(a.phase));
        check(result.bus, "ALE", e.pin_bitfield0.ale, a.ale);
        if (word_bus) { check(result.bus, "BHE", e.pin_bitfield1.bhe, a.bhe); }

        // MOO has its own bus-status numbering. Convert the CPU's S2:S0 pins.
        static constexpr uint8_t moo_bus_status[] = {0, 1, 2, 5, 6, 3, 4, 7};
        check(result.bus, "S2:S0", e.bus_status, moo_bus_status[a.bus_status & 7]);
        check(result.bus, "S4:S3", e.segment_status, a.segment_status);
        check(result.bus, "MRDC/AMWC/MWTC", e.memory_status, a.memory_status);
        check(result.bus, "IORC/AIOWC/IOWC", e.io_status, a.io_status);

        // The V2 address field is the multiplexed bus.
        // Compare an address only while ALE is asserted.
        if (e.pin_bitfield0.ale && a.ale) {
            check(result.bus, "address", e.address_latch, a.address);
        }

        // SST data bytes are only meaningful on the completing T3/Tw transfer.
        const bool expected_data = (e.t_state == 3 || e.t_state == 5) &&
            ((e.memory_status | e.io_status) & 6) != 0;

        if (expected_data) {
            check(result.bus, "data valid", true, a.data_valid);
            if (a.data_valid) {
                check(result.bus, "data", e.data_bus, a.data);
            }
        }

        check(result.queue, "QS1:QS0", e.queue_op_status, static_cast<unsigned>(a.queue_status));
        if (e.queue_op_status == 1 || e.queue_op_status == 3) {
            check(result.queue, "queue byte", e.queue_byte_read, a.queue_byte);
        }
    }
    return result;
}
