// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

struct CycleLogMicrocodeState {
    // Logical microcode address; the description lookup resolves the ROM word.
    uint16_t address = 0;
    bool alu_carry = false;
    bool carry = false;
    uint16_t tmpa = 0;
    uint16_t tmpb = 0;
    uint16_t tmpc = 0;
    bool word_size = false;

    bool operator==(const CycleLogMicrocodeState&) const = default;
};

struct CycleLogEntry {
    std::string text;
    std::optional<CycleLogMicrocodeState> microcode;

    bool operator==(const CycleLogEntry&) const = default;
};

class CycleLogMicrocode {
public:
    // Views refer to static ROM descriptions and remain valid after CPU reset.
    static std::string_view disassembly(uint16_t address, bool is8086 = false);
    static size_t formattedSize(const CycleLogEntry& entry, std::string_view description);
    static void format(const CycleLogEntry& entry, std::string_view description, std::string& line);
};
