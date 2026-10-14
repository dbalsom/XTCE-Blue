// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <algorithm>
#include <array>
#include <deque>
#include <format>
#include <span>
#include <string>
#include <vector>
#include "../cpu_types.h"
#include "../CycleLogMicrocode.h"
#include "../Disassembler.h"
#include "../Logger.h"
#include "GeneratedCpu.h"

namespace xtce::nec {

// The adapter forwards native CPU transfers; the motherboard bus owns any
// width conversion needed by its memory and devices.
template<class BusType>
class Cpu {
public:
    using Core = marty::nec::GeneratedCpu;
    using RunResult = Core::RunResult;
    struct InstructionHistoryEntry { uint16_t cs, ip; std::string disassembly; };

    explicit Cpu(Core::Model model = Core::defaultModel, bool single_instruction = false) : core_(model, single_instruction) {
        logger_.reset();
    }
    BusType* getBus() { return &bus_; }
    uint16_t* getRegisters() { return core_.r.data(); }
    uint16_t* getMainRegisters() { return &core_.r[Core::AX]; }
    uint16_t getRegister(Register reg) const { return core_.r[reg_to_idx(reg)]; }
    void setRegister(Register reg, uint16_t value) { core_.r[reg_to_idx(reg)] = value; }
    uint16_t getRealIP() { return core_.r[Core::IP]; }
    uint16_t getInstructionPointer() const {
        return core_.instructionBoundary() || core_.instructionDone ? core_.nextInstructionPointer() : core_.instructionPointer();
    }
    uint8_t getALU() const { return static_cast<uint8_t>(core_.currentAluOperation()); }
    const char* getExecutionState() const { return core_.executionState(); }
    uint64_t cycle() const { return core_.clocks; }
    uint64_t instructionCount() const { return core_.instructionCount(); }
    bool isHalted() const { return core_.halted(); }
    bool isNativeMode() const { return core_.nativeMode(); }
    void setNmiLine(bool level) { core_.setNmiLine(level); }
    bool singleInstructionDone() const { return core_.instructionDone; }
    Core::Model model() const { return core_.model(); }

    void reset() {
        core_.reset();
        logger_.reset();
        clearCycleLog();
        history_.clear();
        history_bytes_.clear();
        history_count_ = 0;
        cycle_snapshot_ = {};
    }
    void setPrefetchQueue(std::span<const uint8_t> bytes) { core_.installQueue(bytes.data(), bytes.size()); }
    void setBusCycleCapture(bool value) { capture_cycles_ = value; }
    const CpuBusCycle& getBusCycle() const { return cycle_snapshot_; }
    QueueReadState getQueueStatus() const { return static_cast<QueueReadState>(core_.queueStatus()); }
    void setTestNumber(uint32_t) {}

    RunResult run_for(int cycles) {
        Host host{bus_};
        if (!capture_cycles_ && !cycle_logging_ && !history_enabled_) {
            core_.runFor(host, static_cast<uint64_t>(std::max(cycles, 0)));
        } else {
            core_.beginRun();
            for (int n = 0; n < cycles && !core_.executionStopped(); ++n) { simulateCycle(host); }
        }
        return core_.stopReason();
    }
    int stepToNextInstruction() {
        Host host{bus_};
        core_.beginRun();
        const auto start = core_.instructionCount();
        for (int n = 1; n <= 1000000; ++n) {
            simulateCycle(host);
            if (core_.executionStopped() || core_.instructionCount() != start || core_.halted()) { return n; }
        }
        return 1000000;
    }

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
    void setLogInstructions(bool enabled) { history_enabled_ = enabled; history_bytes_.clear(); }
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
    void beginCycleLogFrame() {}
    void endCycleLogFrame() {}
    bool isCycleLogging() const { return cycle_logging_; }
    void clearCycleLog() {
        if (!cycle_log_.empty()) { ++cycle_log_revision_; }
        cycle_log_.clear();
    }
    void setCycleLogCapacity(size_t capacity) {
        log_capacity_ = capacity;
        if (cycle_log_.size() > capacity) { ++cycle_log_revision_; }
        while (cycle_log_.size() > capacity) { cycle_log_.pop_front(); }
    }
    const std::deque<CycleLogEntry>& getCycleLogBuffer() const { return cycle_log_; }
    size_t getCycleLogSize() const { return cycle_log_.size(); }
    uint64_t getCycleLogRevision() const { return cycle_log_revision_; }
    size_t getCycleLogCapacity() const { return log_capacity_; }
    void appendCycleLogLine(std::string line) { appendCycleLogEntry({std::move(line), std::nullopt}); }
    std::string_view getMicrocodeDisassembly(uint16_t address) const { return core_.microcodeDisassembly(address); }
    void formatCycleLogEntry(const CycleLogEntry& entry, std::string& line) const {
        CycleLogMicrocode::format(entry,
            entry.microcode ? getMicrocodeDisassembly(entry.microcode->address) : std::string_view{}, line);
    }
    std::string getQueueDebugString() const {
        std::string text;
        for (size_t n = 0; n < core_.queueSize(); ++n) {
            text += std::format("{:02X}[{:04X}] ", core_.queueByte(n), uint16_t(core_.r[Core::IP] + n));
        }
        return text;
    }

private:
    struct CycleLogBusSignals {
        bool aen = false, dma_s3 = false, dma_delayed_t2 = false, interrupt_pending = false;
        uint8_t dma = 0, dmas = 0, irqs = 0;
        int pit = 0;
        BusStatus bus_operation = BusStatus::Passive;
        uint32_t dma_address = 0;
    };

    CycleLogBusSignals cycleLogBusSignals() {
        CycleLogBusSignals signals;
        signals.interrupt_pending = bus_.interruptPending();
        // Minimal CPU test buses have no motherboard diagnostics.
        if constexpr (requires { bus_.getAEN(); bus_.getDMAS3(); bus_.getDMADelayedT2(); bus_.getDMA();
                                 bus_.getDMAS(); bus_.getIRQLines(); bus_.pitBits();
                                 bus_.getBusOperation(); bus_.getDMAAddress(); }) {
            signals.aen = bus_.getAEN();
            signals.dma_s3 = bus_.getDMAS3();
            signals.dma_delayed_t2 = bus_.getDMADelayedT2();
            signals.dma = bus_.getDMA();
            signals.dmas = static_cast<uint8_t>(bus_.getDMAS());
            signals.irqs = static_cast<uint8_t>(bus_.getIRQLines());
            signals.pit = bus_.pitBits();
            signals.bus_operation = bus_.getBusOperation();
            if (signals.dma_s3) {
                signals.dma_address = bus_.getDMAAddress();
            }
        }
        return signals;
    }

    struct Host {
        BusType& bus;
        void tick() { bus.tick(); }
        bool ready() { return bus.ready(); }
        bool interruptPending() { return bus.interruptPending(); }
        void setLock(bool value) { bus.setLock(value); }
        void setPassiveOrHalt(bool value) { bus.setPassiveOrHalt(value); }
        void driveWriteData(uint16_t value) { bus.driveWriteData(value); }
        void startAccess(uint32_t address, unsigned bytes, bool fetch, bool io, bool write, bool acknowledge) {
            const auto status = acknowledge ? BusStatus::InterruptAcknowledge : fetch ? BusStatus::InstructionFetch :
                io ? (write ? BusStatus::IoWrite : BusStatus::IoRead) :
                     (write ? BusStatus::MemoryWrite : BusStatus::MemoryRead);
            bus.startAccess(address, status, bytes);
        }
        uint16_t read(uint32_t address, unsigned bytes, bool fetch, bool io, uint64_t) {
            const auto operation = fetch ? BusStatus::InstructionFetch : io ? BusStatus::IoRead : BusStatus::MemoryRead;
            return bus.readTransfer(address, bytes, operation);
        }
        void write(uint32_t address, uint16_t value, unsigned bytes, bool io, uint64_t) {
            bus.writeTransfer(address, value, bytes, io ? BusStatus::IoWrite : BusStatus::MemoryWrite);
        }
        uint16_t acknowledge() { bus.startAccess(0, BusStatus::InterruptAcknowledge); return bus.read(); }
    };

    void appendCycleLogEntry(CycleLogEntry entry) {
        if (!log_capacity_) { return; }
        if (cycle_log_.size() == log_capacity_) { cycle_log_.pop_front(); }
        cycle_log_.push_back(std::move(entry));
        ++cycle_log_revision_;
    }
    void simulateCycle(Host& host) {
        if (!capture_cycles_ && !cycle_logging_ && !history_enabled_) {
            core_.clockFast(host);
            return;
        }
        const auto signals = cycle_logging_ ? cycleLogBusSignals() : CycleLogBusSignals{};
        const auto pins = core_.clock(host);
        if (capture_cycles_ || cycle_logging_) {
            cycle_snapshot_ = {};
            cycle_snapshot_.phase = pins.t;
            cycle_snapshot_.ale = pins.ale;
            cycle_snapshot_.bhe = pins.bhe;
            cycle_snapshot_.address = pins.address;
            cycle_snapshot_.bus_status = pins.status;
            cycle_snapshot_.segment_status = pins.segment;
            cycle_snapshot_.memory_status = pins.memory;
            cycle_snapshot_.io_status = pins.io;
            cycle_snapshot_.data_valid = (pins.t == TState::T3 || pins.t == TState::TWait) && pins.ready;
            cycle_snapshot_.data = pins.data;
            cycle_snapshot_.queue_status = static_cast<QueueReadState>(pins.queueStatus());
            cycle_snapshot_.queue_byte = pins.queueByte;
        }
        if (cycle_logging_) {
            updateLogger(pins, signals);
            const auto queue_status = static_cast<QueueReadState>(pins.queueStatus());
            if (log_capacity_) {
                // Keep the same four visible queue slots and column widths as Intel.
                std::array<uint8_t, 4> queue{};
                const auto count = std::min(queue.size(), core_.queueSize());
                for (size_t i = 0; i < count; ++i) {
                    queue[i] = core_.queueByte(i);
                }
                CycleLogEntry entry{logger_.getLine(std::span<const uint8_t>(queue.data(), count),
                    queue_status, pins.queueByte, queue.size()), std::nullopt};
                if (pins.microcodePointer >= 0) {
                    entry.microcode = CycleLogMicrocodeState{uint16_t(pins.microcodePointer), core_.aluCarry(),
                        (core_.r[Core::FLAGS] & Core::CF) != 0, core_.r[Core::TA], core_.r[Core::TB], core_.r[Core::TC], core_.wordSize, 15};
                }
                appendCycleLogEntry(std::move(entry));
            }
            else {
                logger_.advance(queue_status, pins.queueByte);
            }
        }
        if (history_enabled_) { recordHistory(pins); }
    }

    void updateLogger(const Core::Cycle& pins, const CycleLogBusSignals& signals) {
        logger_.setAEN(signals.aen);
        auto cycle = cycle_snapshot_;
        if (pins.t == TState::TIdle && core_.halted()) {
            cycle.bus_status = static_cast<uint8_t>(BusStatus::Halt);
        }
        logger_.setCpuCycle(cycle, pins.multiplexed, pins.ready);
        logger_.setDMA(signals.dma);
        logger_.setDMAS(signals.dmas);
        logger_.setPITBits(signals.pit);
        logger_.setIRQs(signals.irqs);
        logger_.setINT(signals.interrupt_pending);
        logger_.setLock(pins.lock);
        if (signals.aen) {
            logger_.setBusOperation(signals.bus_operation);
        }
        if (signals.dma_s3) {
            logger_.setDmaAddress(signals.dma_address);
        }
        else if (signals.dma_delayed_t2) {
            logger_.restoreCpuAddress();
        }
        // The shared disassembler knows 8086 instructions. Do not mislabel
        // 8080 instructions or NEC extensions as Intel opcodes.
        if (!core_.nativeMode()) {
            logger_.setDisassemblyEnabled(false);
        }
        else if (pins.queueStatus() == 1) {
            logger_.setDisassemblyEnabled(pins.queueByte != 0x0f &&
                (pins.queueByte < 0x60 || pins.queueByte > 0x6f));
        }
    }
    void recordHistory(const Core::Cycle& pins) {
        if (pins.qs0) {
            if (history_bytes_.empty()) {
                history_cs_ = core_.instructionSegment();
                history_ip_ = core_.instructionPointer();
                history_native_ = core_.nativeMode();
            }
            history_bytes_.push_back(pins.queueByte);
        }
        if (history_count_ == core_.instructionCount()) { return; }
        history_count_ = core_.instructionCount();
        if (history_bytes_.empty()) { return; }
        std::string text = history_native_ ? "NEC " : "8080 ";
        for (auto byte : history_bytes_) { text += std::format("{:02X} ", byte); }
        // Use the established x86 disassembler where it recognizes the stream.
        size_t opcode_index = 0;
        while (opcode_index < history_bytes_.size()) {
            const auto byte = history_bytes_[opcode_index];
            if (byte != 0x26 && byte != 0x2e && byte != 0x36 && byte != 0x3e &&
                byte != 0xf0 && byte != 0xf2 && byte != 0xf3) { break; }
            ++opcode_index;
        }
        const bool known_native = opcode_index < history_bytes_.size() && history_bytes_[opcode_index] != 0x0f &&
            (history_bytes_[opcode_index] < 0x60 || history_bytes_[opcode_index] > 0x6f);
        if (history_native_ && known_native && history_bytes_.size() <= Disassembler::MAX_INSTRUCTION_BYTES) {
            Disassembler disassembler;
            std::string decoded;
            for (size_t n = 0; n < history_bytes_.size(); ++n) {
                if (disassembler.disassemble(history_bytes_[n], n == 0, decoded)) { text = decoded; }
            }
        }
        history_.push_back({history_cs_, history_ip_, std::move(text)});
        if (history_.size() > 1000) { history_.pop_front(); }
        history_bytes_.clear();
    }

    BusType bus_;
    Core core_;
    Logger logger_;
    bool capture_cycles_ = false, cycle_logging_ = false, history_enabled_ = false;
    size_t log_capacity_ = 1000;
    uint64_t cycle_log_revision_ = 0, history_count_ = 0;
    uint16_t history_cs_ = 0, history_ip_ = 0;
    bool history_native_ = true;
    CpuBusCycle cycle_snapshot_{};
    std::deque<CycleLogEntry> cycle_log_;
    std::deque<InstructionHistoryEntry> history_;
    std::vector<uint8_t> history_bytes_;
};

} // namespace xtce::nec
