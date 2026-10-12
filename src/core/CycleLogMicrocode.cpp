// SPDX-License-Identifier: MIT
#include "CycleLogMicrocode.h"

#include <format>
#include <iterator>

#include "generated_808X/GeneratedCpu.h"

std::string_view CycleLogMicrocode::disassembly(uint16_t address, bool is8086) {
    using Core = marty::intel::GeneratedCpu;
    const auto model = is8086 ? Core::Model::Intel8086 : Core::Model::Intel8088;
    const char* description = Core::microcodeDisassembly(address, model);
    return description ? std::string_view(description) : std::string_view{};
}

size_t CycleLogMicrocode::formattedSize(const CycleLogEntry& entry, std::string_view description, bool include_text) {
    const size_t text_size = include_text ? entry.text.size() : 0;
    if (!entry.microcode || description.empty()) {
        return text_size;
    }
    constexpr size_t suffix_size =
        sizeof("  000000000.0000 alu_CF: 0 CF: 0 tA: 0000 tB: 0000 tC: 0000 wordSize: 8") - 1;
    return text_size + description.size() + suffix_size + (entry.microcode->word_size ? 1 : 0);
}

void CycleLogMicrocode::format(const CycleLogEntry& entry, std::string_view description, std::string& line,
                              bool include_text) {
    line.reserve(formattedSize(entry, description, include_text));
    line.clear();
    if (include_text) {
        line.assign(entry.text);
    }
    if (!entry.microcode || description.empty()) {
        return;
    }
    const auto& state = *entry.microcode;
    line += description;
    line += "  ";
    for (int bit = 12; bit >= 0; --bit) {
        line += (state.address & (1 << bit)) ? '1' : '0';
        if (bit == 4) {
            line += '.';
        }
    }
    std::format_to(std::back_inserter(line),
                   " alu_CF: {} CF: {} tA: {:04X} tB: {:04X} tC: {:04X} wordSize: {}",
                   state.alu_carry ? 1 : 0, state.carry ? 1 : 0, state.tmpa, state.tmpb, state.tmpc,
                   state.word_size ? "16" : "8");
}
