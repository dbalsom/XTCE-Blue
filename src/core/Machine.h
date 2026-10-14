#pragma once
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include "CpuSelection.h"
#include "generated_808X/Cpu.h"
#include "generated_VX0/Cpu.h"
#include "interpreted_808X/Cpu.h"

enum class MachineState
{
    Running,
    Stopped,
    BreakpointHit
};

class Machine
{
    template <class Function>
    decltype(auto) visitCpu(Function&& function) const {
        if (nec_) {
            return function(*nec_);
        }
        if (selection_.execution == CpuExecution::Generated) {
            return function(*generated_);
        }
        return function(*interpreted_);
    }

public:
    struct InstructionHistoryEntry
    {
        uint16_t cs, ip;
        std::string disassembly;
    };
    explicit Machine(CpuSelection selection = {}) : selection_(selection) {
        validateMachineCpu(selection);
        if (cpuFamily(selection.model) == CpuFamily::Nec) {
            using Model = marty::nec::GeneratedCpu::Model;
            nec_ = std::make_unique<xtce::nec::Cpu<Bus>>(selection.model == CpuModel::NecV30 ? Model::V30 : Model::V20);
        }
        else if (selection.execution == CpuExecution::Generated) {
            using Model = marty::intel::GeneratedCpu::Model;
            generated_ = std::make_unique<xtce::generated::Cpu<Bus>>(
                selection.model == CpuModel::Intel8086 ? Model::Intel8086 : Model::Intel8088);
        }
        else {
            interpreted_ = std::make_unique<Cpu<Bus>>();
        }
        resetMachine();
        visitCpu(
            [](auto& cpu)
            {
                cpu.setLogInstructions(false);
                cpu.setOffRailsDetection(true, 20);
            });
    }
    Machine(const Machine&) = delete;
    Machine& operator=(const Machine&) = delete;
    Machine(Machine&&) = delete;
    Machine& operator=(Machine&&) = delete;

    CpuSelection getCpuSelection() const { return selection_; }
    std::string getCpuName() const { return cpuSelectionName(selection_); }

    void run_for(uint64_t ticks) {
        const bool stopped = visitCpu(
            [&](auto& cpu)
            {
                using Result = typename std::remove_reference_t<decltype(cpu)>::RunResult;
                const auto result = cpu.run_for(static_cast<int>(ticks / 3));
                return result == Result::BreakpointHit || result == Result::OffRails;
            });
        if (stopped) {
            state_ = MachineState::BreakpointHit;
        }
    }

    void resetCpu() {
        visitCpu([](auto& cpu) { cpu.reset(); });
    }

    void resetMachine() {
        last_pit_ticks_ = 0;
        resetCpu();
        getBus()->reset();
    }

    uint64_t getElapsedPitTicks(bool new_frame) {
        const auto ticks = getBus()->pit()->getTicks();
        const auto elapsed = ticks - last_pit_ticks_;
        if (new_frame) {
            last_pit_ticks_ = ticks;
        }
        return elapsed;
    }

    void setState(MachineState state) { state_ = state; }

    MachineState getState() const { return state_; }

    std::string getStateString() const {
        switch (state_) {
            case MachineState::Running:
                return "Running";
            case MachineState::Stopped:
                return "Stopped";
            case MachineState::BreakpointHit:
                return "Breakpoint Hit";
        }
        return "Unknown";
    }

    bool isRunning() const { return state_ == MachineState::Running; }
    void stop() { state_ = MachineState::Stopped; }
    void run() { state_ = MachineState::Running; }

    Bus* getBus() {
        return visitCpu([](auto& cpu) { return cpu.getBus(); });
    }
    uint8_t* ram() { return getBus()->ram(); }
    size_t ramSize() { return getBus()->ramSize(); }
    size_t romSize() { return getBus()->romSize(); }
    uint8_t peekPhysical(uint32_t address) { return getBus()->peek(address); }
    void sendScanCode(uint8_t code) { getBus()->enqueueScanCode(code); }
    uint16_t* registers() {
        return visitCpu([](auto& cpu) { return cpu.getRegisters(); });
    }
    uint16_t* getMainRegisters() {
        return visitCpu([](auto& cpu) { return cpu.getMainRegisters(); });
    }
    uint16_t getRealIP() {
        return visitCpu([](auto& cpu) { return cpu.getRealIP(); });
    }
    uint16_t getInstructionPointer() const {
        return visitCpu([](auto& cpu) { return cpu.getInstructionPointer(); });
    }
    uint8_t getALU() const {
        return visitCpu([](auto& cpu) { return cpu.getALU(); });
    }
    std::string getQueueDebugString() const {
        return visitCpu([](auto& cpu) { return cpu.getQueueDebugString(); });
    }

    const char* getExecutionState() const {
        if (nec_) {
            return nec_->getExecutionState();
        }
        if (generated_) {
            return generated_->getExecutionState();
        }
        static constexpr const char* names[] = {"Running",
                                                "Waiting for queue data",
                                                "Waiting for queue idle",
                                                "IO delay 2",
                                                "IO delay 1",
                                                "Waiting for first byte to start",
                                                "Waiting for first byte",
                                                "Waiting for second byte",
                                                "Single cycle wait",
                                                "Halting start",
                                                "Halting 3",
                                                "Halting 2",
                                                "Halting 1",
                                                "Halted",
                                                "Suspending"};
        return names[static_cast<unsigned>(interpreted_->getMCState())];
    }

    uint64_t cycleCount() const {
        return visitCpu([](auto& cpu) { return cpu.cycle(); });
    }
    uint64_t instructionCount() const {
        return visitCpu([](auto& cpu) { return cpu.instructionCount(); });
    }
    uint64_t stepInstruction() {
        const auto cycles = visitCpu([](auto& cpu) { return cpu.stepToNextInstruction(); });
        if (state_ == MachineState::Running) {
            state_ = MachineState::Stopped;
        }
        return static_cast<uint64_t>(cycles);
    }

    void setBreakpoint(uint16_t cs, uint16_t ip) {
        visitCpu([&](auto& cpu) { cpu.setBreakpoint(cs, ip); });
    }
    void clearBreakpoint() {
        visitCpu([](auto& cpu) { cpu.clearBreakpoint(); });
    }
    bool hasBreakpoint() const {
        return visitCpu([](auto& cpu) { return cpu.hasBreakpoint(); });
    }
    bool breakpointHit() const {
        return visitCpu([](auto& cpu) { return cpu.breakpointHit(); });
    }
    void clearBreakpointHit() {
        visitCpu([](auto& cpu) { cpu.clearBreakpointHit(); });
    }
    uint16_t breakpointCS() const {
        return visitCpu([](auto& cpu) { return cpu.breakpointCS(); });
    }
    uint16_t breakpointIP() const {
        return visitCpu([](auto& cpu) { return cpu.breakpointIP(); });
    }
    void setSoftwareInterruptBreakpoint(uint8_t vector) {
        visitCpu([&](auto& cpu) { cpu.setSoftwareInterruptBreakpoint(vector); });
    }
    void clearSoftwareInterruptBreakpoint() {
        visitCpu([](auto& cpu) { cpu.clearSoftwareInterruptBreakpoint(); });
    }

    void setLogInstructions(bool enabled) {
        visitCpu([&](auto& cpu) { cpu.setLogInstructions(enabled); });
    }
    bool isLogInstructions() const {
        return visitCpu([](auto& cpu) { return cpu.isLogInstructions(); });
    }
    std::vector<InstructionHistoryEntry> getHistory(size_t lines) const {
        return visitCpu(
            [&](auto& cpu)
            {
                std::vector<InstructionHistoryEntry> entries;
                for (auto& entry : cpu.getHistory(lines)) {
                    entries.push_back({entry.cs, entry.ip, std::move(entry.disassembly)});
                }
                return entries;
            });
    }

    // Cycle logging
    void setCycleLogging(bool enabled) {
        visitCpu([&](auto& cpu) { cpu.setCycleLogging(enabled); });
    }
    void beginCycleLogFrame() {
        visitCpu([](auto& cpu) { cpu.beginCycleLogFrame(); });
    }
    void endCycleLogFrame() {
        visitCpu([](auto& cpu) { cpu.endCycleLogFrame(); });
    }
    bool isCycleLogging() const {
        return visitCpu([](auto& cpu) { return cpu.isCycleLogging(); });
    }
    void clearCycleLog() {
        visitCpu([](auto& cpu) { cpu.clearCycleLog(); });
    }
    void setCycleLogCapacity(size_t capacity) {
        visitCpu([&](auto& cpu) { cpu.setCycleLogCapacity(capacity); });
    }
    const std::deque<CycleLogEntry>& getCycleLogBuffer() const {
        return visitCpu([](auto& cpu) -> const std::deque<CycleLogEntry>& { return cpu.getCycleLogBuffer(); });
    }
    size_t getCycleLogSize() const {
        return visitCpu([](auto& cpu) { return cpu.getCycleLogSize(); });
    }
    uint64_t getCycleLogRevision() const {
        return visitCpu([](auto& cpu) { return cpu.getCycleLogRevision(); });
    }
    size_t getCycleLogCapacity() const {
        return visitCpu([](auto& cpu) { return cpu.getCycleLogCapacity(); });
    }
    void appendCycleLogLine(const std::string& line) {
        visitCpu([&](auto& cpu) { cpu.appendCycleLogLine(line); });
    }
    std::string_view getMicrocodeDisassembly(uint16_t address) const {
        return visitCpu([&](auto& cpu) { return cpu.getMicrocodeDisassembly(address); });
    }
    void formatCycleLogEntry(const CycleLogEntry& entry, std::string& line) const {
        visitCpu([&](auto& cpu) { cpu.formatCycleLogEntry(entry, line); });
    }

private:
    CpuSelection selection_;
    MachineState state_ = MachineState::Stopped;
    uint64_t last_pit_ticks_ = 0;
    std::unique_ptr<Cpu<Bus>> interpreted_;
    std::unique_ptr<xtce::generated::Cpu<Bus>> generated_;
    std::unique_ptr<xtce::nec::Cpu<Bus>> nec_;
};
