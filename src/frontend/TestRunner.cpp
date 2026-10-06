// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#include <format>

#include "SingleStep.h"
#include "SstComparison.h"
#include "TestRunner.h"

#include <ranges>

Register MooRegToRegister(const Moo::REG16 reg) {
    switch (reg) {
        case Moo::REG16::AX:
            return Register::AX;
        case Moo::REG16::BX:
            return Register::BX;
        case Moo::REG16::CX:
            return Register::CX;
        case Moo::REG16::DX:
            return Register::DX;
        case Moo::REG16::CS:
            return Register::CS;
        case Moo::REG16::SS:
            return Register::SS;
        case Moo::REG16::DS:
            return Register::DS;
        case Moo::REG16::ES:
            return Register::ES;
        case Moo::REG16::SP:
            return Register::SP;
        case Moo::REG16::BP:
            return Register::BP;
        case Moo::REG16::SI:
            return Register::SI;
        case Moo::REG16::DI:
            return Register::DI;
        case Moo::REG16::IP:
            return Register::PC;
        case Moo::REG16::FLAGS:
            return Register::FLAGS;
        default:
            throw std::runtime_error("Unknown MOO REG16");
    }
}

// Convert internal Register enum to a human-readable string (for test reporting)
static std::string GetRegisterString(Register r) {
    static const char* names[] = {"ES",  "CS",   "SS",   "DS",   "IP",    "IND", "OPR", "R7", "R8", "R9",    "R10",
                                  "R11", "TMPA", "TMPB", "TMPC", "FLAGS", "R16", "R17", "M",  "R",  "SIGMA", "ONES",
                                  "R22", "R23",  "AX",   "CX",   "DX",    "BX",  "SP",  "BP", "SI", "DI"};
    const auto idx = static_cast<size_t>(r);
    return names[idx];
}

// Print differences between two 8088 FLAGS values. Returns a short textual summary of changed flags.
static std::string printFlagDiff(uint16_t expected, uint16_t actual) {
    // Consider the 8088 flags of interest and omit reserved bits.
    // bit positions: 0 CF, 2 PF, 4 AF, 6 ZF, 7 SF, 8 TF, 9 IF, 10 DF, 11 OF
    static const std::pair<int, const char*> flagMap[] = {{0, "CF"}, {2, "PF"}, {4, "AF"},  {6, "ZF"}, {7, "SF"},
                                                          {8, "TF"}, {9, "IF"}, {10, "DF"}, {11, "OF"}};

    std::string out;
    bool first = true;
    for (const auto& p : flagMap) {
        const int bit = p.first;
        const char* name = p.second;
        const int e = (expected >> bit) & 1;
        const int a = (actual >> bit) & 1;
        if (e != a) {
            if (!first)
                out += "; ";
            out += std::format("{}:e{},a{}", name, e, a);
            first = false;
        }
    }
    if (out.empty()) {
        return std::string("(no bit-level differences detected)");
    }
    return out;
}

bool TestRunner::runAllTests(size_t max_tests) {

    bool all_ok = true;
    for (const auto& filepath : files_) {
        if (!runTestFile(filepath, max_tests)) {
            all_ok = false;
        }
    }

    // Print a summary of test results
    printSummary();

    return all_ok;
}

bool TestRunner::runTestFile(const std::filesystem::path& filepath, size_t max_tests) {
    Moo::Reader reader;

    std::cout << "Loading MOO file: " << filepath << "\n";
    reader.AddFromFile(filepath.generic_string());

    std::cout << "\n========================================\n";
    std::cout << "MOO File Information\n";
    std::cout << "========================================\n";
    const auto header = reader.GetHeader();
    const auto version = header.GetVersion();
    std::cout << "Version: " << static_cast<int>(version.first) << "." << static_cast<int>(version.second) << "\n";
    std::cout << "CPU: " << header.cpu_name << "\n";
    std::cout << "Test Count: " << header.test_count << "\n";

    auto ctx = TestContext{.cpu = Cpu<StubBus>(), .max_tests = max_tests};

    bool file_ok = true;
    // Run up to max_tests for this file (if max_tests == 0, run all)
    size_t per_file_count = 0;
    for (const auto& test : reader) {
        if (max_tests != 0 && per_file_count >= max_tests) {
            break; // per-file cap reached
        }
        if (!runTest(ctx, test, filepath)) {
            file_ok = false;
        }
        ++per_file_count;
    }

    ++total_files_run_;
    return file_ok;
}

bool TestRunner::runTest(TestContext& ctx, const Moo::Reader::Test& test, const std::filesystem::path& filepath) {
    auto& cpu = ctx.cpu;
    cpu.reset();
    cpu.getBus()->reset();

    ++total_tests_run_;
    const auto fname = filepath.filename().string();
    auto& summary = file_summaries_[fname];
    ++summary.total;

    for (const auto r : Moo::REG16Range()) {
        cpu.setRegister(MooRegToRegister(r), test.GetInitialRegister(r));
    }
    for (const auto& [address, value] : test.init_state.ram) {
        cpu.getBus()->ram()[address & 0xfffff] = value;
    }
    const auto prefetched = std::min(test.bytes.size(), test.init_state.queue.bytes.size());
    cpu.getBus()->setInstructionFetchBytes(test.bytes.size() - prefetched);
    cpu.setPrefetchQueue(test.init_state.queue.bytes);
    cpu.setBusCycleCapture(true);

    // Keep diagnostics limited to 3 failing tests per file.
    // Every failed test still contributes to the per-category totals.
    constexpr size_t detail_limit = 3;
    const bool save_detail = summary.details_saved < detail_limit;
    cpu.setCycleLogging(save_detail);
    cpu.setCycleLogCapacity(64);
    cpu.setTestNumber(test.index);

    std::vector<CpuBusCycle> trace;
    trace.reserve(test.cycles.size());

    const auto step = runSingleStepObserved(cpu, test.bytes.size(), [&](int) { trace.push_back(cpu.getBusCycle()); });

    auto [timing, bus, queue] = compareSstTrace(test.cycles, trace);
    if (test.cycles.empty()) {
        timing = "SST has no cycle trace to validate";
    }

    bool reg_failed = false;
    bool ip_failed = false;
    bool flag_failed = false;
    bool mem_failed = false;
    std::string message;
    auto add_message = [&](const std::string& text)
    {
        if (save_detail && !text.empty()) {
            if (!message.empty())
                message += "\n  ";
            message += text;
        }
    };

    if (!step.completed) {
        add_message("Timed out waiting for the next instruction's first-byte queue status");
    }

    add_message(timing);
    add_message(bus);
    add_message(queue);

    for (const auto r : Moo::REG16Range()) {
        uint16_t expected = test.GetFinalRegister(r, false);
        // PC is the BIU fetch pointer. At the terminating first-byte signal,
        // the address of the newly decoded instruction is the architectural IP.
        uint16_t actual = r == Moo::REG16::IP ? cpu.getInstructionPointer() : cpu.getRegister(MooRegToRegister(r));

        if (test.final_state.masks.HasRegister(r)) {
            expected &= test.final_state.masks.GetRegister(r);
            actual &= test.final_state.masks.GetRegister(r);
        }

        if (actual == expected) {
            continue;
        }

        if (r == Moo::REG16::FLAGS) {
            flag_failed = true;
            add_message(std::format("FLAGS: expected {:04X}, got {:04X} | {}", expected, actual,
                                    printFlagDiff(expected, actual)));
        }
        else {
            if (r == Moo::REG16::IP) {
                ip_failed = true;
            }
            else {
                reg_failed = true;
            }
            add_message(std::format("Register {}: expected {:04X}, got {:04X}", GetRegisterString(MooRegToRegister(r)),
                                    expected, actual));
        }
    }
    for (const auto& [address, expected] : test.final_state.ram) {
        const auto actual = cpu.getBus()->ram()[address & 0xfffff];
        if (actual != expected) {
            if (!mem_failed) {
                add_message(std::format("Memory[{:#07X}]: expected {:02X}, got {:02X}", address, expected, actual));
            }
            mem_failed = true;
        }
    }
    const bool timing_failed = !timing.empty();
    const bool bus_failed = !bus.empty();
    const bool queue_failed = !queue.empty();
    const bool failed = !step.completed || reg_failed || ip_failed || flag_failed || mem_failed || timing_failed ||
        bus_failed || queue_failed;

    if (failed) {
        ++total_failed_;
        ++summary.failed;
        summary.reg_failed += reg_failed;
        summary.ip_failed += ip_failed;
        summary.flag_failed += flag_failed;
        summary.mem_failed += mem_failed;
        summary.timing_failed += timing_failed;
        summary.bus_failed += bus_failed;
        summary.queue_failed += queue_failed;
        summary.timeout_failed += !step.completed;
        total_flag_failed_ += flag_failed;

        if (save_detail) {
            FailureDetail detail{};
            detail.file = fname;
            detail.test_index = test.index;
            detail.test_name = test.name;
            if (test.has_hash) {
                for (auto byte : test.hash)
                    detail.test_hash += std::format("{:02x}", byte);
            }
            detail.cycles_taken = step.instruction_cycles;
            detail.message = std::move(message);
            for (const auto r : Moo::REG16Range()) {
                detail.regs.push_back(r == Moo::REG16::IP ? cpu.getInstructionPointer()
                                                          : cpu.getRegister(MooRegToRegister(r)));
            }
            detail.cycle_logs = cpu.getCycleLogBuffer();
            failure_details_.push_back(std::move(detail));
            ++summary.details_saved;
        }
    }
    else {
        ++total_passed_;
        ++summary.passed;
    }
    return !failed;
}

// Print registers in a compact grouped format from a snapshot vector taken in Moo::REG16 order.
static void printRegisters(const std::vector<uint16_t>& regs, int indent = 0, std::ostream& os = std::cout) {
    // Build a mapping from Moo::REG16 -> value using the same iteration order used when capturing the snapshot.
    std::unordered_map<int, uint16_t> map;
    size_t i = 0;
    for (const auto r : Moo::REG16Range()) {
        if (i < regs.size())
            map[static_cast<int>(r)] = regs[i++];
    }

    auto get = [&](Moo::REG16 r) -> uint16_t
    {
        auto it = map.find(static_cast<int>(r));
        return it != map.end() ? it->second : 0;
    };

    // Create padding string
    const std::string pad(indent, ' ');

    // Helper to format 16-bit hex
    auto hx = [](uint16_t v) { return std::format("{:04X}", static_cast<unsigned>(v)); };

    // Primary/general registers
    os << pad
       << std::format("AX: {} BX: {} CX: {} DX: {}\n", hx(get(Moo::REG16::AX)), hx(get(Moo::REG16::BX)),
                      hx(get(Moo::REG16::CX)), hx(get(Moo::REG16::DX)));
    // Index/stack regs
    os << pad
       << std::format("SI: {} DI: {} BP: {} SP: {}\n", hx(get(Moo::REG16::SI)), hx(get(Moo::REG16::DI)),
                      hx(get(Moo::REG16::BP)), hx(get(Moo::REG16::SP)));
    // Segment registers
    os << pad
       << std::format("CS: {} DS: {} ES: {} SS: {}\n", hx(get(Moo::REG16::CS)), hx(get(Moo::REG16::DS)),
                      hx(get(Moo::REG16::ES)), hx(get(Moo::REG16::SS)));
    // IP and FLAGS
    const uint16_t ip = get(Moo::REG16::IP);
    const uint16_t flags = get(Moo::REG16::FLAGS);
    os << pad << std::format("IP:*{}    FLAGS:*{} ", hx(ip), hx(flags));

    // Compact FLAGS decode: produce a compact bit+letter sequence e.g. "1o0d1i..."
    struct FlagInfo
    {
        int bit;
        char code;
        const char* name;
    };
    static const FlagInfo flagOrder[] = {{11, 'o', "OF"}, {10, 'd', "DF"}, {9, 'i', "IF"},
                                         {8, 't', "TF"},  {7, 's', "SF"},  {6, 'z', "ZF"},
                                         {4, 'a', "AF"},  {2, 'p', "PF"},  {0, 'c', "CF"}};

    std::string compact;
    for (const auto& f : flagOrder) {
        const int val = (flags >> f.bit) & 1;
        compact += (val ? '1' : '0');
        compact += f.code;
    }

    os << compact;
    os << '\n';
}

void TestRunner::printSummary() const {
    FileSummary totals;
    std::vector<std::pair<std::string, FileSummary>> items(file_summaries_.begin(), file_summaries_.end());
    std::ranges::sort(items, [](const auto& a, const auto& b) { return a.first < b.first; });

    for (const auto& s : items | std::views::values) {
        totals.ip_failed += s.ip_failed;
        totals.timing_failed += s.timing_failed;
        totals.bus_failed += s.bus_failed;
        totals.queue_failed += s.queue_failed;
        totals.timeout_failed += s.timeout_failed;
    }

    std::cout << std::format("\n====== Test Summary ======\nFiles: {}\nTests run: {}\nPassed: {}\nFailed: {}\n"
                             "Flag failures: {}\nIP failures: {}\nTiming failures: {}\nBus failures: {}\n"
                             "Queue failures: {}\nTimeouts: {}\n",
                             total_files_run_, total_tests_run_, total_passed_, total_failed_, total_flag_failed_,
                             totals.ip_failed, totals.timing_failed, totals.bus_failed, totals.queue_failed,
                             totals.timeout_failed);

    std::cout << "\nPer-file results (counts are tests; failure categories may overlap):\n";

    constexpr auto row = "{:<20}{:>9}{:>9}{:>9}{:>11}{:>11}{:>11}{:>10}{:>10}{:>10}{:>10}{:>9}\n";
    std::cout << std::format(row, "File", "Total", "Passed", "Failed", "RegFailed", "MemFailed", "FlagFailed",
                             "IPFailed", "Timing", "Bus", "Queue", "Timeout");

    std::cout << std::string(129, '-') << "\n";

    for (const auto& [name, s] : items) {
        std::cout << std::format(row, name, s.total, s.passed, s.failed, s.reg_failed, s.mem_failed, s.flag_failed,
                                 s.ip_failed, s.timing_failed, s.bus_failed, s.queue_failed, s.timeout_failed);
    }

    std::cout << "==========================\n";

    if (!failure_details_.empty()) {
        std::cout << "\nFailure samples (first 3 failing tests per file; first difference per signal category):\n";

        for (const auto& fd : failure_details_) {
            std::cout << std::format("File: {} Test [{:05}]: {}\n  Hash: {}\n  {}\n  Instruction cycles: {}\n", f,
                                     fd.test_index, fd.test_name, fd.test_hash, fd.message, fd.cycles_taken);

            printRegisters(fd.regs, 2);

            for (const auto& line : fd.cycle_logs) {
                std::cout << "    " << line << "\n";
            }
        }
    }
}
