// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once
#include <algorithm>
#include <cassert>
#include <deque>
#include <format>
#include <span>
#include <string>
#include <utility>
#include <vector>
#include "../CycleLogMicrocode.h"
#include "../Disassembler.h"
#include "../Logger.h"
#include "../cpu_types.h"
#include "GeneratedCpu.h"

// XTCE-facing adapter for the generated Intel CPU core.
namespace xtce::generated
{

template <class BusType>
class Cpu
{
    template <bool Log>
    struct Host;

public:
    using Core = marty::intel::GeneratedCpu;
    using RunResult = Core::RunResult;
    struct InstructionHistoryEntry
    {
        uint16_t cs, ip;
        std::string disassembly;
    };

    BusType* getBus() { return &bus_; }
    uint16_t* getRegisters() { return core_.registers_; }
    uint16_t* getMainRegisters() { return &core_.registers_[24]; }
    uint16_t getRegister(Register reg) const { return core_.registers_[reg_to_idx(reg)]; }
    void setRegister(Register reg, uint16_t value) { core_.registers_[reg_to_idx(reg)] = value; }
    uint16_t getRealIP() { return uint16_t(core_.pc() - core_.queue_bytes_); }
    uint16_t getInstructionPointer() const {
        return core_.instructionBoundary() ? core_.nextInstructionPointer() : core_.instructionPointer();
    }
    uint8_t getALU() const { return static_cast<uint8_t>(core_.alu_); }
    const char* getExecutionState() const { return core_.executionState(); }
    uint64_t cycle() const { return core_.cycleCount(); }
    uint64_t instructionCount() const { return core_.instructionCount(); }
    bool isHalted() const { return core_.halted(); }

    void reset() {
        core_.reset();
        clearCycleLog();
        history_.clear();
        disassembler_.reset();
        logger_.reset();
        cycle_snapshot_ = {};
    }

    void setPrefetchQueue(std::span<const uint8_t> bytes) { core_.setPrefetchQueue(bytes.begin(), bytes.end()); }
    void setBusCycleCapture(bool value) { capture_cycles_ = value; }
    const CpuBusCycle& getBusCycle() const { return cycle_snapshot_; }
    QueueReadState getQueueStatus() const { return static_cast<QueueReadState>(core_.queueStatus()); }
    void setTestNumber(uint32_t) {}

    RunResult run_for(int cycles) {
        const auto clocks = static_cast<uint64_t>(std::max(cycles, 0));
        if (!capture_cycles_ && !cycle_logging_ && !history_enabled_) {
            Host<false> host{bus_};
            core_.runFor(host, clocks);
        }
        else if (cycle_logging_) {
            Host<true> host{bus_};
            runCycleLoop(host, clocks);
        }
        else {
            Host<false> host{bus_};
            runCycleLoop(host, clocks);
        }
        return core_.stopReason();
    }

    int stepToNextInstruction() {
        if (cycle_logging_) {
            Host<true> host{bus_};
            return stepWithHost(host);
        }
        Host<false> host{bus_};
        return stepWithHost(host);
    }

private:
    template <bool Log>
    int stepWithHost(Host<Log>& host) {
        core_.beginRun();
        const auto instructions = core_.instructionCount();
        for (int n = 1; n <= 1000000; ++n) {
            simulateCycle(host);
            if (core_.executionStopped() || (core_.instructionBoundary() && core_.instructionCount() > instructions) ||
                core_.halted()) {
                return n;
            }
        }
        return 1000000;
    }

public:
    void setBreakpoint(uint16_t cs, uint16_t ip) { core_.setBreakpoint(cs, ip); }
    void clearBreakpoint() { core_.clearBreakpoint(); }
    bool hasBreakpoint() const { return core_.hasBreakpoint(); }
    bool breakpointHit() const { return core_.breakpointHit(); }
    void clearBreakpointHit() { core_.clearBreakpointHit(); }
    uint16_t breakpointCS() const { return core_.breakpointCS(); }
    uint16_t breakpointIP() const { return core_.breakpointIP(); }
    void setSoftwareInterruptBreakpoint(uint8_t vector) { core_.setSoftwareInterruptBreakpoint(vector); }
    void clearSoftwareInterruptBreakpoint() { core_.clearSoftwareInterruptBreakpoint(); }
    void setOffRailsDetection(bool enabled, int maximum = 20) { core_.setOffRailsDetection(enabled, maximum); }
    void setLogInstructions(bool enabled) { history_enabled_ = enabled; }
    bool isLogInstructions() const { return history_enabled_; }
    std::vector<InstructionHistoryEntry> getHistory(size_t lines) const {
        const auto count = std::min(lines, history_.size());
        return {history_.rbegin(), history_.rbegin() + count};
    }
    void setCycleLogging(bool enabled) {
        if (enabled && !cycle_logging_) {
            logger_.beginLogging();
        }
        cycle_logging_ = enabled;
    }
    void beginCycleLogFrame() {
        defer_cycle_log_ = cycle_logging_;
        deferred_cycle_log_.clear();
    }
    void endCycleLogFrame() {
        for (auto& cycle : deferred_cycle_log_) {
            appendCycleLogEntry(
                {cycle.logger.getLine(cycle.queue, cycle.queue_status, cycle.queue_byte, 4), cycle.microcode});
        }
        deferred_cycle_log_.clear();
        defer_cycle_log_ = false;
    }
    bool isCycleLogging() const { return cycle_logging_; }
    void clearCycleLog() {
        if (!cycle_log_.empty()) {
            ++cycle_log_revision_;
        }
        cycle_log_.clear();
        deferred_cycle_log_.clear();
    }
    void setCycleLogCapacity(size_t capacity) {
        log_capacity_ = capacity;
        if (cycle_log_.size() > log_capacity_) {
            ++cycle_log_revision_;
        }
        while (cycle_log_.size() > log_capacity_) {
            cycle_log_.pop_front();
        }
        while (deferred_cycle_log_.size() > log_capacity_) {
            deferred_cycle_log_.pop_front();
        }
    }
    const std::deque<CycleLogEntry>& getCycleLogBuffer() const { return cycle_log_; }
    size_t getCycleLogSize() const { return cycle_log_.size(); }
    uint64_t getCycleLogRevision() const { return cycle_log_revision_; }
    size_t getCycleLogCapacity() const { return log_capacity_; }
    void appendCycleLogLine(std::string line) { appendCycleLogEntry({std::move(line), std::nullopt}); }
    std::string_view getMicrocodeDisassembly(uint16_t address) const {
        return CycleLogMicrocode::disassembly(address, core_.is8086());
    }
    void formatCycleLogEntry(const CycleLogEntry& entry, std::string& line) const {
        CycleLogMicrocode::format(
            entry, entry.microcode ? getMicrocodeDisassembly(entry.microcode->address) : std::string_view{}, line);
    }
    std::string getQueueDebugString() const {
        std::string result;
        for (std::size_t i = 0; i < core_.queue.size(); ++i) {
            const auto& entry = core_.queue.entry(i);
            result += std::format("{:02X}[{:04X}] ", entry.data, entry.address);
        }
        return result;
    }

private:
    void appendCycleLogEntry(CycleLogEntry entry) {
        if (log_capacity_ == 0) {
            return;
        }
        if (cycle_log_.size() == log_capacity_) {
            cycle_log_.pop_front();
        }
        cycle_log_.push_back(std::move(entry));
        ++cycle_log_revision_;
    }

    struct CycleLogBusSignals
    {
        bool aen = false, dma_s3 = false, dma_delayed_t2 = false, interrupt_pending = false;
        uint8_t dma = 0, dmas = 0, irqs = 0;
        int pit = 0;
        BusStatus bus_operation = BusStatus::Passive;
        uint32_t dma_address = 0;
    };

    struct DeferredCycleLog
    {
        Logger logger;
        marty::intel::PrefetchQueue queue;
        QueueReadState queue_status;
        uint8_t queue_byte;
        std::optional<CycleLogMicrocodeState> microcode;
    };

    template <bool Log>
    struct Host
    {
        BusType& bus;
        CycleLogBusSignals signals{};
        void startAccess(uint32_t address, BusStatus bus_status, unsigned width) {
            assert(width == 1 && "XTCE byte bus requires an 8088");
            bus.startAccess(address, bus_status);
        }
        bool ready() { return bus.ready(); }
        uint16_t read() { return bus.read(); }
        void write(uint16_t value) { bus.write(static_cast<uint8_t>(value)); }
        void tick() {
            if constexpr (Log) {
                const bool dma_s3 = bus.getDMAS3();
                signals = {bus.getAEN(),
                           dma_s3,
                           bus.getDMADelayedT2(),
                           bus.interruptPending(),
                           bus.getDMA(),
                           static_cast<uint8_t>(bus.getDMAS()),
                           static_cast<uint8_t>(bus.getIRQLines()),
                           bus.pitBits(),
                           bus.getBusOperation(),
                           dma_s3 ? bus.getDMAAddress() : 0};
            }
            bus.tick();
        }
        bool interruptPending() { return bus.interruptPending(); }
        void setLock(bool value) { bus.setLock(value); }
        void setPassiveOrHalt(bool value) { bus.setPassiveOrHalt(value); }
    };

    template <bool Log>
    void runCycleLoop(Host<Log>& host, uint64_t clocks) {
        core_.beginRun();
        for (uint64_t n = 0; n < clocks; ++n) {
            simulateCycle(host);
            if (core_.executionStopped()) {
                break;
            }
        }
    }

    template <bool Log>
    void simulateCycle(Host<Log>& host) {
        if (capture_cycles_ || cycle_logging_) {
            Core::Cycle pins;
            core_.clockWithCycles(host, pins);
            recordCycle(core_, pins, host.signals);
        }
        else {
            core_.clock(host);
        }
        if (history_enabled_) {
            recordInstructionHistory();
        }
    }

    void recordCycle(const Core& cpu, const Core::Cycle& pins, const CycleLogBusSignals& signals) {
        if (capture_cycles_) {
            cycle_snapshot_ = {};
            cycle_snapshot_.phase = pins.t;
            cycle_snapshot_.ale = pins.ale;
            cycle_snapshot_.address = pins.address;
            cycle_snapshot_.bus_status = pins.status;
            cycle_snapshot_.segment_status = pins.segment;
            cycle_snapshot_.memory_status = pins.memory;
            cycle_snapshot_.io_status = pins.io;
            cycle_snapshot_.data_valid = (pins.t == TState::T3 || pins.t == TState::TWait) &&
                static_cast<BusStatus>(pins.status) == BusStatus::Passive;
            cycle_snapshot_.data = static_cast<uint8_t>(pins.data);
            cycle_snapshot_.queue_status = static_cast<QueueReadState>(pins.queueStatus());
            cycle_snapshot_.queue_byte = pins.queueByte;
        }
        if (cycle_logging_) {
            updateLogger(pins, signals);
            const auto queue_status = static_cast<QueueReadState>(pins.queueStatus());
            if (log_capacity_ != 0) {
                std::optional<CycleLogMicrocodeState> microcode;
                if (pins.microcodePointer >= 0) {
                    microcode = CycleLogMicrocodeState{static_cast<uint16_t>(pins.microcodePointer),
                                                       cpu.getAluCF(),
                                                       (cpu.registers_[15] & 1) != 0,
                                                       cpu.registers_[12],
                                                       cpu.registers_[13],
                                                       cpu.registers_[14],
                                                       cpu.word_size_};
                }
                if (defer_cycle_log_) {
                    if (deferred_cycle_log_.size() == log_capacity_) {
                        deferred_cycle_log_.pop_front();
                    }
                    deferred_cycle_log_.push_back({logger_, cpu.queue, queue_status, pins.queueByte, microcode});
                    logger_.advance(queue_status, pins.queueByte);
                }
                else {
                    appendCycleLogEntry({logger_.getLine(cpu.queue, queue_status, pins.queueByte, 4), microcode});
                }
            }
            else {
                logger_.advance(queue_status, pins.queueByte);
            }
        }
    }

    void updateLogger(const Core::Cycle& pins, const CycleLogBusSignals& signals) {
        const auto bus_status = static_cast<BusStatus>(pins.status);
        const auto next_bus_status = static_cast<BusStatus>(pins.nextIoType);
        if (pins.t == TState::T1) {
            logger_.setCpuAddress(pins.address);
        }
        if (pins.t == TState::T2) {
            static constexpr int segments[] = {0, 2, 1, 3};
            logger_.setStatusHigh(segments[pins.segment]);
            logger_.setBusOperation(bus_status);
            if (bus_status == BusStatus::IoWrite || bus_status == BusStatus::MemoryWrite) {
                logger_.setData(static_cast<uint8_t>(pins.address));
            }
        }
        if ((pins.t == TState::T3 || pins.t == TState::TWait) && pins.ready &&
            (pins.memory == 4 || pins.io == 4 || next_bus_status == BusStatus::InterruptAcknowledge)) {
            logger_.setData(static_cast<uint8_t>(pins.data));
        }
        if ((pins.t == TState::T3 || pins.t == TState::TWait) && pins.ready) {
            logger_.setStatus(BusStatus::Passive);
        }
        if (pins.loggerStatus >= 0) {
            logger_.setStatus(static_cast<BusStatus>(pins.loggerStatus));
        }
        if (pins.nextBus == TState::T1 && (pins.t == TState::TIdle || pins.t == TState::T4) &&
            next_bus_status != BusStatus::Passive) {
            logger_.setStatus(next_bus_status);
        }
        logger_.setAEN(signals.aen);
        logger_.setDMA(signals.dma);
        logger_.setPITBits(signals.pit);
        logger_.setBusOperation(signals.bus_operation);
        logger_.setInterruptFlag(pins.interruptFlag);
        if (signals.dma_s3) {
            logger_.setDmaAddress(signals.dma_address);
        }
        else if (signals.dma_delayed_t2) {
            logger_.restoreCpuAddress();
            logger_.setBusOperation(next_bus_status);
        }
        logger_.setReady(pins.ready);
        logger_.setLock(pins.lock);
        logger_.setDMAS(signals.dmas);
        logger_.setIRQs(signals.irqs);
        logger_.setINT(signals.interrupt_pending);
    }

    void recordInstructionHistory() {
        const auto& cpu = core_;
        if (cpu.queueStatus() == 1 || cpu.queueStatus() == 3) {
            std::string instruction;
            if (disassembler_.disassemble(cpu.queueByte(), cpu.queueStatus() == 1, instruction)) {
                history_.push_back({cpu.instructionSegment(), cpu.instructionPointer(), std::move(instruction)});
                if (history_.size() > 1000) {
                    history_.pop_front();
                }
            }
        }
    }

    BusType bus_;
    Core core_{Core::Model::Intel8088};

    // Cycle log stuff
    bool capture_cycles_ = false, cycle_logging_ = false, history_enabled_ = false;
    size_t log_capacity_ = 1000;
    CpuBusCycle cycle_snapshot_{};
    std::deque<CycleLogEntry> cycle_log_;
    uint64_t cycle_log_revision_ = 0;
    std::deque<DeferredCycleLog> deferred_cycle_log_;
    bool defer_cycle_log_ = false;

    // Instruction History
    std::deque<InstructionHistoryEntry> history_;

    // Disassembly & Logging
    Disassembler disassembler_;
    Logger logger_;
};

} // namespace xtce::generated
