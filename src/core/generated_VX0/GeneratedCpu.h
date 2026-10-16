// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include "cpu_types.h"
#include "execution_control.h"

// Keep ALU setup shared between dispatch cases to limit generated code size.
#if defined(_MSC_VER)
#define MARTY_NEC_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define MARTY_NEC_NOINLINE __attribute__((noinline))
#else
#define MARTY_NEC_NOINLINE
#endif

namespace marty::nec
{

class GeneratedCpu final : public ::cpu::ExecutionControl
{
public:
    enum Reg : unsigned
    {
        ES = 0,
        CS = 1,
        SS = 2,
        DS = 3,
        IP = 4,
        IND = 5,
        OPR = 6,
        TA = 12,
        TB = 13,
        TC = 14,
        FLAGS = 15,
        LC = 17,
        AX = 24,
        CX = 25,
        DX = 26,
        BX = 27,
        SP = 28,
        BP = 29,
        SI = 30,
        DI = 31,
        REG_COUNT = 32
    };

    static constexpr uint16_t CF = 0x0001;
    static constexpr uint16_t PF = 0x0004;
    static constexpr uint16_t AF = 0x0010;
    static constexpr uint16_t ZF = 0x0040;
    static constexpr uint16_t SF = 0x0080;
    static constexpr uint16_t TF = 0x0100;
    static constexpr uint16_t IF = 0x0200;
    static constexpr uint16_t DF = 0x0400;
    static constexpr uint16_t OF = 0x0800;
    static constexpr uint16_t MF = 0x8000;

    static constexpr uint16_t ALU_FLAGS = CF | PF | AF | ZF | SF | OF;
    static constexpr uint16_t CONTROL_FLAGS = TF | IF | DF;
    static constexpr uint16_t FIXED_FLAGS = 0x7002; // Reserved bits read as one.

    enum class Model
    {
        V30,
        V20
    };
    static const Model defaultModel;
    enum class Segment
    {
        ES,
        Io,
        SS,
        Default
    };
    enum class Alu
    {
        Add,
        Or,
        Adc,
        Sbb,
        And,
        Sub,
        Xor,
        Cmp,
        Rol,
        Ror,
        Rcl,
        Rcr,
        Shl,
        Shr,
        Sar,
        Rol12,
        Div,
        Mul,
        AdjustDecimal,
        AdjustAscii,
        BitMask,
        Inc,
        Dec,
        Not,
        Neg,
        Inc2,
        Dec2,
        MulDiv,
        Pass,
        Unsupported
    };

    enum class InstructionGroup : uint8_t
    {
        Bitfield = 0x3,
        ModrmEntry = 0xb,
        IncDec = 0xc,
        Dad = 0xd
    };

    struct InstructionInfo
    {
        uint16_t entry;
        bool word, modrm, readEa, writeEa, direction, accumulator, segment, miscellaneous;
        // Group ROM outputs 11:14 select a miscellaneous operation or an
        // ordinary instruction family, depending on the miscellaneous bit.
        uint8_t groupOperation, xiBank;

        bool isGroup(InstructionGroup group) const {
            return !miscellaneous && groupOperation == static_cast<uint8_t>(group);
        }
    };

    static const InstructionInfo opcodeDecodeTable[1024];
    static const Alu xiBanks[][8];

    Model model() const { return model_; }
    Alu currentAluOperation() const { return alu_operation_; }
    const char* microcodeDisassembly(uint16_t address) const;
    // Debugger/diagnostic lookup only; execution switches on the full address.
    uint16_t microcodeListingLine(uint16_t address) const;
    uint16_t currentLine() const { return microcodeListingLine(last_micro_address_); }
    bool nativeMode() const { return (r[FLAGS] & MF) != 0; }
    bool halted() const { return halted_; }
    void setNmiLine(bool level) {
        nmi_pending_ = nmi_pending_ || (level && !nmi_line_);
        nmi_line_ = level;
    }
    bool instructionBoundary() const { return !instructionStarted; }
    uint16_t instructionPointer() const { return instruction_start_ip_; }
    uint16_t instructionSegment() const { return instruction_start_cs_; }
    uint16_t nextInstructionPointer() const { return r[IP]; }
    uint64_t instructionCount() const { return instruction_count_; }
    size_t queueCapacity() const { return model_ == Model::V20 ? 4 : 6; }
    uint8_t queueStatus() const { return queue_status_; }
    const char* executionState() const {
        if (halted_) {
            return "Halted";
        }
        if (micro_state_ == MicroState::WaitingForQueueData) {
            return "Waiting for queue data";
        }
        if (micro_state_ == MicroState::WaitingForOperand) {
            return "Waiting for bus";
        }
        if (micro_state_ == MicroState::WaitingForRequestSlot) {
            return "Waiting for bus request slot";
        }
        if (micro_state_ == MicroState::WaitingForPrefetch) {
            return "Waiting for prefetch";
        }
        return "Running";
    }

    void executeMicrocode(uint16_t address);

#include "microcode_conditions.inc"


    void enterEmulation() {
        mode_flag_writable_ = true;
        r[FLAGS] &= ~MF;
    }
    void leaveEmulation() {
        mode_flag_writable_ = false;
        r[FLAGS] |= MF;
    }
    void deferInterrupt() { interrupt_delay_ = 2; }
    void requestInterruptAcknowledge() {
        wordSize = true;
        const BiuRequest request{0, 0, 2, 0, false, false, true};
        beginRequest(request);
    }

    template <class Bus>
    uint64_t runFor(Bus& bus, uint64_t cycles) {
        beginRun();
        const auto start = clocks;
        while (clocks - start < cycles && !executionStopped()) {
            clockFast(bus);
        }
        return clocks - start;
    }

    // Cycle snapshot for diagnostic or debugger use.
    struct Cycle
    {
        uint32_t address = 0, multiplexed = 0;
        uint16_t data = 0;
        TState t = TState::TIdle;
        uint8_t status = 7, memory = 0, io = 0, segment = 4;
        uint8_t queueByte = 0;
        bool ready = true;
        int microcodePointer = -1;
        bool ale = false, bhe = false, lock = false, qs0 = false, qs1 = false;

        uint8_t queueStatus() const { return uint8_t(qs0) | (uint8_t(qs1) << 1); }
    };

    struct Operand
    {
        enum class Kind
        {
            Word,
            Byte,
            Segment,
            Memory
        };
        Kind kind = Kind::Word;
        uint8_t index = 0;
    };

    // Indexed by Reg; general-purpose registers are contiguous from AX.
    std::array<uint16_t, REG_COUNT> r{};
    Operand op1, op2;
    Alu decodedAluOperation = Alu::Pass;
    uint8_t opcode = 0, modrm = 0, prefixCount = 0;
    bool wordSize = true, endRequested = false;
    bool busyPin = false, interruptPending = false;
    uint16_t k = 0xffff, microAddress = 0;
    uint64_t clocks = 0, microSteps = 0;
    bool instructionStarted = false, instructionDone = false;
    Cycle pins; // Last captured clock; clockFast/runFor leave this unchanged.

    explicit GeneratedCpu(Model model = defaultModel, bool singleInstruction = false) :
        model_(model), single_instruction_(singleInstruction) {

        r[CS] = 0xffff; // Reset vector
        r[FLAGS] = (MF | FIXED_FLAGS); // Default flags
    }

    // Reset the CPU
    void reset() {
        const auto controls = static_cast<const ::cpu::ExecutionControl&>(*this);
        *this = GeneratedCpu(model_, single_instruction_);
        static_cast<::cpu::ExecutionControl&>(*this) = controls;
        resetExecutionControl();
    }

    // Handle unsupported instructions by throwing an exception with a detailed message.
    [[noreturn]] void unsupported(const char* detail) const {
        std::ostringstream message;
        message << "unsupported " << detail << "; opcode=" << std::hex << unsigned(opcode) << " uaddr=" << microAddress
                << " line=" << currentLine();
        throw std::runtime_error(message.str());
    }

    // Sign-extend a byte to a word.
    static uint16_t extendByte(uint16_t value) {
        return (value & 0x80) != 0 ? uint16_t(value | 0xff00) : uint16_t(value & 0xff);
    }

    // Read a byte from the specified index in the register file.
    uint8_t readByteReg(unsigned index) const { return uint8_t(r[AX + (index & 3)] >> ((index & 4) ? 8 : 0)); }

    // Write a byte to the specified index in the register file.
    void writeByteReg(unsigned index, uint16_t value) {
        if (!instruction_native_ && decodedAluOperation == Alu::Cmp && index == 0) {
            return;
        }
        auto& reg = r[AX + (index & 3)];
        const unsigned shift = (index & 4) ? 8 : 0;
        reg = uint16_t((reg & ~(0xffu << shift)) | ((value & 0xff) << shift));
    }

    void writeSegment(unsigned index, uint16_t value, bool from_operand = false) {
        r[index & 3] = value;
        if (index == CS) {
            cs_clock_ = clocks;
            cs_transfer_pending_ = from_operand;
        }
        if (index == SS) {
            deferInterrupt();
        }
    }

    // Return the byte-swapped value of AX
    uint16_t swappedAccumulator() const { return uint16_t((r[AX] << 8) | (r[AX] >> 8)); }

    // Return the value of the source 'K', an operation-dependent constant.
    uint16_t readK() {
        if (alu_operation_ == Alu::BitMask) {
            evaluateAlu();
        }
        else if (alu_operation_ == Alu::AdjustDecimal || alu_operation_ == Alu::AdjustAscii) {
            adjust_kind_ = alu_operation_;

            const bool decimal = alu_operation_ == Alu::AdjustDecimal;
            const uint8_t value = r[instruction_native_ ? TB : TA];
            const auto flags = r[FLAGS];
            const bool af = (flags & AF) != 0;

            adjust_auxiliary_ = af || (value & 0x0f) > 9;
            adjust_carry_ = decimal ? (flags & CF) || value > (af ? 0x9f : 0x99) : adjust_auxiliary_;

            k = (adjust_auxiliary_ ? 0x06 : 0) | (decimal && adjust_carry_ ? 0x60 : 0);
        }

        return k;
    }

    // Read the value of the memory operand (OPR) and mark it as invalid.
    uint16_t readOpr() {
        opr_valid_ = false;
        return r[OPR];
    }

    // Write a value to the memory operand (OPR) and mark it as valid.
    void writeOpr(uint16_t value) {
        r[OPR] = value;
        opr_valid_ = true;
        opr_clock_ = clocks;

        // Execute a pending memory write on OPR resolution
        if (request_pending_ && active_request_.write && !write_data_ready_) {
            supplyWriteData();
        }
    }

    // Read the instruction operand
    uint16_t readOperand(Operand operand) {
        switch (operand.kind) {
            case Operand::Kind::Word:
                // Read a word from the general-purpose register file.
                return r[AX + operand.index];
            case Operand::Kind::Byte:
                // Read a byte from the general-purpose register file.
                return readByteReg(operand.index);
            case Operand::Kind::Segment:
                // Read a segment register
                return r[operand.index & 3];
            case Operand::Kind::Memory:
                // Read a memory operand (OPR)
                return readOpr();
        }

        throw std::logic_error("invalid operand");
    }

    // Write a value to the instruction operand
    void writeOperand(Operand operand, uint16_t value) {
        if (decodedAluOperation == Alu::Cmp) {
            // CMP computes flags without writing back to the operand.
            return;
        }

        switch (operand.kind) {
            case Operand::Kind::Word:
                // Write a word to the general-purpose register file.
                r[AX + operand.index] = value;
                break;
            case Operand::Kind::Byte:
                // Write a byte to the general-purpose register file.
                writeByteReg(operand.index, value);
                break;
            case Operand::Kind::Segment:
                // Write a value to a segment register.
                writeSegment(operand.index, value);
                break;
            case Operand::Kind::Memory:
                // Write a value to the memory operand (OPR)
                writeOpr(value);
                break;
        }
    }

    // Write to the IND register
    void writeIndex(uint16_t value) {
        r[IND] = value;
        index_write_clock_ = clocks;
        index_pending_ = true;
    }

    // Read the PC register
    uint16_t readPc() {
        // A recently sampled PC still needs an address-adder clock when
        // SIGMA supplies the FLUSH target (short JMP and LOOP).
        pc_read_clock_ = clocks;
        return r[IP];
    }

    // Copy a value to the FLAGS register (with masking for reserved and emulation bits)
    void writeFlags(uint16_t value) {
        r[FLAGS] = (value & (ALU_FLAGS | CONTROL_FLAGS)) | FIXED_FLAGS | (mode_flag_writable_ ? (value & MF) : MF);
    }

    // Return the step size for the direction flag (DF) in the FLAGS register
    uint16_t directionStep() const { return uint16_t((r[FLAGS] & DF) ? -(wordSize ? 2 : 1) : (wordSize ? 2 : 1)); }

    // Install an initial set of bytes into the prefetch queue, simulating a prefetch.
    // Used for SingleStepTest execution.
    void installQueue(const uint8_t* bytes, size_t count) {
        if (count > queueCapacity()) {
            throw std::runtime_error("initial queue exceeds model capacity");
        }

        prefetch_head_ = prefetch_count_ = 0;
        pending_prefetch_bytes_ = prefetch_publish_delay_ = 0;
        fetch_blocked_ = fetch_restart_pending_ = false;
        pfp_ = r[IP];

        for (size_t n = 0; n < count; ++n) {
            enqueue(bytes[n]);
            ++pfp_;
        }

        prefetch_start_delay_ = count ? 2 : 0;

        if (count) {
            const uint32_t lastAddress = (uint32_t(r[CS]) << 4) + uint16_t(pfp_ - 1);
            multiplexed_ = 0x20000 | (r[FLAGS] & IF ? 0x40000 : 0) | (lastAddress & 0xff00) | bytes[count - 1];
        }
    }

    // Return the number of bytes currently in the prefetch queue.
    size_t queueSize() const { return prefetch_count_; }

    // Return the number of prefetched bytes currently visible to microcode.
    size_t microcodePrefetchBytes() const {
        // Microcode receives the BIU data a clock before its external QS signal.
        return prefetch_count_ + (prefetch_publish_delay_ == 1 ? pending_prefetch_bytes_ : 0);
    }

    // Read a byte from the prefetch queue for microcode, using early publication when available.
    uint8_t readPrefetchForMicrocode() {
        if (!prefetch_count_ && prefetch_publish_delay_ == 1) {
            publishPrefetch();
        }
        const auto status = queue_status_;
        const auto byte = queue_byte_;
        const auto value = readQueue();
        next_queue_status_ = queue_status_;
        next_queue_byte_ = queue_byte_;
        queue_status_ = status;
        queue_byte_ = byte;

        return value;
    }

    // Peek at a byte in the prefetch queue without consuming it.
    uint8_t queueByte(size_t index) const { return prefetch_queue_[(prefetch_head_ + index) % prefetch_queue_.size()]; }

    // Read a byte from the prefetch queue, consuming it.
    uint8_t readQueue(bool first = false) {
        if (!prefetch_count_) {
            throw std::logic_error("queue underflow");
        }

        const uint8_t value = prefetch_queue_[prefetch_head_];

        // Interrupt breakpoint hook
        if (!first && !extended_opcode_ && nativeMode() && opcode == 0xcd) {
            checkSoftwareInterruptBreakpoint(0xcd, value);
        }

        prefetch_head_ = (prefetch_head_ + 1) % prefetch_queue_.size();
        --prefetch_count_;

        if (fetch_blocked_) {
            fetch_blocked_ = false;
            // A fetch already in flight reserves its queue slot. If that made
            // the queue full, restart arbitration after that fetch completes.
            fetch_restart_pending_ = t_state_ != TState::TIdle && bus_prefetch_;
            prefetch_start_delay_ = prefetch_publish_delay_ ? prefetch_publish_delay_ + 1 : 2;
        }

        // Advance PC as the EU consumes an instruction byte.
        ++r[IP];
        queue_status_ = first ? 1 : 3;
        queue_byte_ = value;
        return value;
    }

    // Wait until enough prefetched bytes are available to microcode.
    void waitForQueue(unsigned bytes) {
        waiting_queue_bytes_ = bytes;
        micro_state_ = MicroState::WaitingForQueueData;
    }

    void latchOprFromRead() {
        if (read_count_) {
            opr_latch_pending_ = false;
            r[OPR] = read_results_[read_head_];
            opr_valid_ = true;
            opr_clock_ = clocks;
            read_head_ = (read_head_ + 1) % read_results_.size();
            --read_count_;
        }
    }

    // Request the operand latch to be filled (implements 'F' signal)
    void requestOprLatch() {
        // F can request the read latch without using OPR in this word.
        // Independent transfers may then run and queue a dependent write.
        if (read_count_) {
            latchOprFromRead();
        }
        else if ((request_pending_ && !active_request_.write) || (request_queued_ && !queued_request_.write)) {
            opr_latch_pending_ = true;
        }
    }

    // Returns true if the current instruction uses a byte immediate value.
    bool shortImmediate() const {
        // Not sure how these are determined in hardware - there isn't a bit in
        // the group decode ROM that discriminates them.
        return !wordSize || (!extended_opcode_ && (opcode == 0x83 || opcode == 0x6a || opcode == 0x6b));
    }

    // Execute SUSP to suspend prefetching.
    // The BIU sees SUSP after two clocks; its acknowledgement reaches
    // the EU one clock later. An already selected fetch can still start.
    void suspendPrefetch() { suspend_delay_ = 3; }

    // Return if the prefetch queue is ready to be flushed, optionally waiting
    // for the BIU to acknowledge.
    bool prefetchFlushReady(bool wait_for_biu = true) {
        // A continuing, non-F word posts FLUSH while the EU proceeds to MW.
        // A FLUSH with no preceding SUSP also posts its own suspend request.
        if (!wait_for_biu && !flush_pending_) {
            return true;
        }
        if (!flush_pending_ && !suspend_delay_ && !prefetch_suspended_) {
            return true;
        }
        if (!flush_pending_ && !suspend_delay_ && !(t_state_ != TState::TIdle && bus_prefetch_)) {
            return true;
        }
        micro_state_ = MicroState::WaitingForPrefetch;
        return false;
    }

    // Flush the prefetch queue.
    void flushPrefetch(bool from_operand = false, bool from_alu = false, bool end_asserted = true) {
        if ((!end_asserted && !from_operand) || (!suspend_delay_ && !prefetch_suspended_)) {
            // Preserve the requested IP while later words use PC. Suspension
            // can still admit the last already selected old-stream prefetch.
            flush_pending_ = true;
            flush_delay_ = end_asserted ? 2 : 3;
            flush_ip_ = r[IP];
            flush_from_operand_ = from_operand;
            flush_from_alu_ = from_alu;
            if (!suspend_delay_ && !prefetch_suspended_) {
                suspendPrefetch();
            }
            return;
        }
        completePrefetchFlush(r[IP], from_operand, from_alu);
    }

    // Complete the prefetch queue flush
    void completePrefetchFlush(uint16_t target, bool from_operand, bool from_alu) {
        // RETF and far indirect JMP load CS from OPR before the FLUSH word.
        // A CS transfer from a temporary does not use this operand pipeline.
        from_operand |= cs_transfer_pending_ && clocks - cs_clock_ < 3;
        cs_transfer_pending_ = false;
        prefetch_head_ = prefetch_count_ = 0;
        pending_prefetch_bytes_ = prefetch_publish_delay_ = 0;
        fetch_blocked_ = fetch_restart_pending_ = false;
        pfp_ = target;
        ++fetch_generation_;
        prefetch_suspended_ = false;
        suspend_delay_ = 0;

        // An OPR target crosses to the BIU on the next clock. Its fetch
        // address is ready after the following address-adder clock.
        const bool late_pc = from_alu && clocks - pc_read_clock_ < 3;
        prefetch_start_delay_ = from_operand ? 2 : late_pc ? 1 : 0;

        // An idle BIU can report empty immediately; an active/just-finished
        // fetch delays that indication until the late target has passed.
        if (from_operand || (late_pc && bus_idle_clocks_ <= 1)) {
            next_queue_status_ = 2;
        }
        else {
            queue_status_ = 2;
        }
    }

    void selectInterruptVector() {
        vector_access_ = true;
        wordSize = true;
    }

    // Perform a local jump within the current 16-slot microcode block.
    void jumpLocal(unsigned target) {
        next_micro_address_ = uint16_t((microAddress & 0x7ff0) | (target & 15));
        micro_branch_delay_ = true;
    }

    // The five-bit far target replaces the block tag.
    // Implements CALL which should probably be renamed FJMP.
    void jumpFar(uint16_t target) {
        next_micro_address_ = target & 0x7fff;
        // The target selection can overlap an F wait for write completion.
        micro_branch_delay_ = !write_waited_;
    }

    bool aluCarry() const { return (alu_flags_ & CF) != 0; }

    bool aluZero() const { return alu_zero_; }

    bool aluLess() const { return bool(alu_flags_ & SF) != bool(alu_flags_ & OF); }

    void captureArithmeticSign() { result_negative_ = absolute_negative_ != bool(r[TB] & (wordSize ? 0x8000 : 0x80)); }

    void beginDecimalString() {
        r[FLAGS] &= ~CF;
        result_negative_ = true;
    }

    void accumulateDecimalZero() { result_negative_ = result_negative_ && aluZero(); }

    bool nonnegativeResult() const { return !result_negative_; }

    bool decrementLoopCounter() { return --r[LC] != 0; }

    bool repeatCondition() {
        if (!decrementLoopCounter()) {
            return false;
        }

        if (opcode == 0xe0 || opcode == 0xe1) {
            return bool(r[FLAGS] & ZF) == bool(opcode & 1);
        }

        if (interruptPending) {
            return false;
        }

        if ((opcode & 0xfe) == 0xa6 || (opcode & 0xfe) == 0xae) {
            if (repeat_prefix_ == 0x64 || repeat_prefix_ == 0x65) {
                return bool(r[FLAGS] & CF) == (repeat_prefix_ == 0x65);
            }

            return bool(r[FLAGS] & ZF) == (repeat_prefix_ == 0xf3);
        }

        return true;
    }

    template <bool alu_repeat, bool writeFlags = false>
    MARTY_NEC_NOINLINE void setupMul(Reg temporary) {
        if constexpr (alu_repeat) {
            // SIGMA supplies the candidate partial sum. A's low bit selects
            // that sum or the unmodified partial product before B:A shifts.
            const uint32_t mask = wordSize ? 0xffff : 0xff;
            const uint32_t high = (r[TA] & 1) ? (r[TB] & mask) | (aluCarry() ? mask + 1 : 0) : alu_old_tmp_b_ & mask;
            // Working model for V20WIDTH's physical V20 captures: byte MUL
            // shifts both bytes of A independently, feeding B bit 0 into
            // bits 7 and 15. Do not discard A's upper byte on each step.
            const uint32_t shift_mask = wordSize ? 0x7fff : 0x7f7f;
            const uint32_t incoming_mask = wordSize ? 0x8000 : 0x8080;
            r[TA] = uint16_t(((r[TA] >> 1) & shift_mask) | ((high & 1) ? incoming_mask : 0));
            r[TB] = uint16_t(high >> 1);
        }
        setupAlu<alu_repeat, writeFlags>(Alu::Mul, temporary);
    }

    template <bool alu_repeat, bool writeFlags = false>
    MARTY_NEC_NOINLINE void setupDiv(Reg temporary) {
        const uint32_t mask = wordSize ? 0xffff : 0xff;
        const uint32_t sign = wordSize ? 0x8000 : 0x80;
        division_negative_ = aluCarry();

        if constexpr (alu_repeat) {
            if (alu_operation_ == Alu::Pass) {
                r[TB] = alu_old_tmp_b_;
            }

            const int32_t partial = int32_t(r[TB] & mask) - (division_negative_ ? int32_t(mask + 1) : 0);
            const int32_t shifted = partial * 2 + ((r[TA] & sign) ? 1 : 0);
            division_high_ = shifted - int32_t(uint32_t(shifted) & mask);
            r[TB] = uint16_t(uint32_t(shifted) & mask);
        }
        else if (division_negative_) {
            r[TB] = uint16_t((r[TB] + r[temporary]) & mask);
        }

        r[TA] = uint16_t(((r[TA] << 1) | !division_negative_) & mask);
        setupAlu<alu_repeat, writeFlags>(Alu::Div, temporary);
    }

    template <bool alu_repeat, bool writeFlags = false>
    MARTY_NEC_NOINLINE void setupDecodedAlu(Reg temporary) {
        if constexpr (alu_repeat) {
            if (decodedAluOperation == Alu::Mul) {
                setupMul<alu_repeat, writeFlags>(temporary);
                return;
            }
        }
        if (decodedAluOperation == Alu::Div) {
            setupDiv<alu_repeat, writeFlags>(temporary);
            return;
        }
        setupAlu<alu_repeat, writeFlags>(decodedAluOperation, temporary);
    }

    // MUL/DIV preparation must observe the previous ALU state before this latch.
    template <bool alu_repeat, bool writeFlags = false>
    MARTY_NEC_NOINLINE void setupAlu(Alu operation, Reg temporary) {
        alu_operation_ = operation;
        alu_temporary_ = temporary;
        alu_commit_flags_on_sigma_ = alu_repeat && writeFlags;

        if constexpr (alu_repeat) {
            if (--r[LC] != 0) {
                next_micro_address_ = microAddress;
            }
            else if (operation == Alu::Rol12 || (!writeFlags && operation >= Alu::Rol && operation <= Alu::Sar)) {
                r[temporary] = evaluateAlu();
            }
            if (!r[LC]) {
                alu_repeat_delay_ = true;
            }
        }
    }

    // Perform the primed ALU operation (execute SIGMA)
    // An ALU operation is performed on the accumulator and a temporary register.
    uint16_t evaluateAlu() {

        const bool wide = wordSize || alu_operation_ == Alu::Inc2 || alu_operation_ == Alu::Dec2;
        const uint32_t mask = wide ? 0xffff : 0xff;
        const uint32_t sign = wide ? 0x8000 : 0x80;
        const uint32_t accumulator = r[TB]; // accumulator
        const uint32_t operand = r[alu_temporary_]; // selected temporary register
        const uint32_t c_in = r[FLAGS] & CF; // carry in
        bool carry = false, overflow = false, auxiliary = false;
        uint32_t result = operand;

        alu_old_tmp_b_ = accumulator;
        alu_flag_mask_ = ALU_FLAGS;

        switch (alu_operation_) {
            case Alu::Add:
            case Alu::Adc:
            case Alu::Mul:
                result = accumulator + operand + (alu_operation_ == Alu::Adc ? c_in : 0);
                carry = (accumulator & mask) + (operand & mask) + (alu_operation_ == Alu::Adc ? c_in : 0) > mask;
                overflow = (~(accumulator ^ operand) & (accumulator ^ result) & sign) != 0;
                auxiliary = ((accumulator ^ operand ^ result) & 0x10) != 0;
                break;
            case Alu::Sub:
            case Alu::Sbb:
            case Alu::Cmp:
                result = accumulator - operand - (alu_operation_ == Alu::Sbb ? c_in : 0);
                carry = (accumulator & mask) < (operand & mask) + (alu_operation_ == Alu::Sbb ? c_in : 0);
                overflow = ((accumulator ^ operand) & (accumulator ^ result) & sign) != 0;
                auxiliary = ((accumulator ^ operand ^ result) & 0x10) != 0;
                break;
            case Alu::Or:
                result = accumulator | operand;
                break;
            case Alu::And:
                result = accumulator & operand;
                break;
            case Alu::Xor:
                result = accumulator ^ operand;
                break;
            case Alu::Inc:
            case Alu::Inc2:
                result = operand + (alu_operation_ == Alu::Inc ? 1 : 2);
                carry = (operand & mask) + (alu_operation_ == Alu::Inc ? 1 : 2) > mask;
                overflow = (operand & mask) == sign - 1;
                auxiliary = ((operand ^ result ^ (alu_operation_ == Alu::Inc ? 1 : 2)) & 0x10) != 0;
                alu_flag_mask_ &= ~CF;
                break;
            case Alu::Dec:
            case Alu::Dec2:
                result = operand - (alu_operation_ == Alu::Dec ? 1 : 2);
                carry = (operand & mask) < (alu_operation_ == Alu::Dec ? 1u : 2u);
                overflow = (operand & mask) == sign;
                auxiliary = ((operand ^ result ^ (alu_operation_ == Alu::Dec ? 1 : 2)) & 0x10) != 0;
                alu_flag_mask_ &= ~CF;
                break;
            case Alu::Not:
                result = ~operand;
                alu_flag_mask_ = 0;
                break;
            case Alu::Neg:
                result = 0 - operand;
                carry = (operand & mask) != 0;
                overflow = (operand & mask) == sign;
                auxiliary = ((operand ^ result) & 0x10) != 0;
                break;
            case Alu::Rol:
                carry = (operand & sign) != 0;
                result = (operand << 1) | unsigned(carry);
                overflow = bool(result & sign) != carry;
                alu_flag_mask_ = (CF | OF);
                break;
            case Alu::Ror:
                carry = (operand & 1) != 0;
                result = ((operand & mask) >> 1) | (carry ? sign : 0);
                overflow = ((result ^ (result << 1)) & sign) != 0;
                alu_flag_mask_ = (CF | OF);
                break;
            case Alu::Rcl:
                carry = (operand & sign) != 0;
                result = (operand << 1) | c_in;
                overflow = bool(result & sign) != carry;
                alu_flag_mask_ = (CF | OF);
                break;
            case Alu::Rcr:
                carry = (operand & 1) != 0;
                result = ((operand & mask) >> 1) | (c_in ? sign : 0);
                overflow = ((result ^ (result << 1)) & sign) != 0;
                alu_flag_mask_ = (CF | OF);
                break;
            case Alu::Shl:
                carry = (operand & sign) != 0;
                result = operand << 1;
                overflow = bool(result & sign) != carry;
                break;
            case Alu::Shr:
                carry = (operand & 1) != 0;
                result = (operand & mask) >> 1;
                overflow = (operand & sign) != 0;
                break;
            case Alu::Sar:
                carry = (operand & 1) != 0;
                result = ((operand & mask) >> 1) | (operand & sign);
                break;
            case Alu::Rol12:
                result = (operand << 1) | ((operand >> 11) & 1);
                alu_flag_mask_ = 0;
                break;
            case Alu::MulDiv:
                absolute_negative_ = (operand & sign) != 0;
                result = absolute_negative_ ? uint16_t(0 - operand) : operand;
                result &= mask;
                break;
            case Alu::AdjustAscii:
                r[alu_temporary_] &= 15;
                result = r[alu_temporary_];
                break;
            case Alu::AdjustDecimal:
            case Alu::Pass:
                result = r[alu_temporary_];
                break;
            case Alu::Div:
                {
                    const int32_t partial = int32_t(accumulator & mask) + division_high_;
                    const int32_t candidate =
                        partial + (division_negative_ ? int32_t(operand & mask) : -int32_t(operand & mask));
                    result = uint32_t(candidate);
                    carry = candidate < 0;
                    break;
                }
            case Alu::BitMask:
                k = uint16_t(1u << (operand & (wide ? 15 : 7)));
                result = k;
                break;
            default:
                unsupported("ALU operation");
                break;
        }

        const bool maskAsciiResult = adjust_kind_ == Alu::AdjustAscii;

        if (adjust_kind_ == Alu::AdjustDecimal || maskAsciiResult) {
            carry = adjust_carry_;
            auxiliary = adjust_auxiliary_;
            adjust_kind_ = Alu::Pass;
        }

        const uint32_t masked = result & mask;

        // PASS always tests zero against the full temporary (including CX for byte REP strings).
        // Keep that microcode condition separate from the operand-sized ZF.
        alu_zero_ = (alu_operation_ == Alu::Pass ? uint16_t(result) : masked) == 0;
        uint8_t parity = uint8_t(masked);

        // Cute parity trick.
        // https://stackoverflow.com/questions/20894110/bit-parity-code-needs-explanation-as-to-how-it-works
        parity ^= parity >> 4;
        parity &= 15;
        alu_flags_ = uint16_t((carry ? CF : 0) | (auxiliary ? AF : 0) | (overflow ? OF : 0) | (masked == 0 ? ZF : 0) |
                              (masked & sign ? SF : 0) | (((0x6996 >> parity) & 1) == 0 ? PF : 0));

        if (!instruction_native_) {
            alu_flag_mask_ &= ~OF;
            if (!extended_opcode_ && decode_info_->isGroup(InstructionGroup::Dad)) {
                r[FLAGS] = (r[FLAGS] & ~CF) | (alu_flags_ & CF); // DAD writes carry only.
            }
        }

        // Set when both R (repeat) and W (write flags) are active.
        if (alu_commit_flags_on_sigma_) {
            commitAluFlags();
        }

        return uint16_t(maskAsciiResult ? result & 15 : result);
    }

    // Commit the internal ALU flags to the FLAGS register.
    void commitAluFlags() { r[FLAGS] = (r[FLAGS] & ~alu_flag_mask_) | (alu_flags_ & alu_flag_mask_); }

    // Request a read from the bus unit.
    void requestRead(Segment segment) { requestTransfer(segment, false); }

    // Request a write to the bus unit.
    void requestWrite(Segment segment, unsigned delay = 2) {
        const bool forwardingRead = read_count_ != 0;
        latchOprFromRead();
        opr_valid_ |= forwardingRead;
        requestTransfer(segment, true, delay);
    }

    void commitOperand() {
        if (!instruction_native_) {
            if (op2.kind == Operand::Kind::Memory) {
                requestWrite(Segment::Default);
            }
            return;
        }
        const bool writesMemory =
            op1.kind == Operand::Kind::Memory || (!decode_info_->direction && op2.kind == Operand::Kind::Memory);

        if (writesMemory && decodedAluOperation != Alu::Cmp) {
            if (ea_write_prepared_) {
                // EA setup already issued this direct transfer.
                // Its first microinstruction supplies OPR.
                ea_write_prepared_ = false;
                return;
            }
            writeIndex(effective_address_);
            requestWrite(Segment::Default, 2);
        }
    }

    // Both paths use the same sequencer.
    // Ordinary execution omits snapshots.
    // Explicit capture retains the clock() interface used by bus validation.
    template <class Bus>
    Cycle clock(Bus& bus) {
        clockImpl<true>(bus);
        return pins;
    }

    // Check whether an F-marked operand access can proceed.
    bool operandAccessReady() {
        // F also appears on words supplying a pending write's data. Those
        // words must run before the transfer, rather than block
        if (read_count_ || (!request_queued_ && (!request_pending_ || request_write_accepted_)) ||
            eu_ == Eu::SupplyingWriteData) {
            return true;
        }
        micro_state_ = MicroState::WaitingForOperand;
        return false;
    }

    // Check whether the BIU has room for another request.
    bool requestSlotReady() {
        if (!request_queued_) {
            return true;
        }
        micro_state_ = MicroState::WaitingForRequestSlot;
        return false;
    }

    template <class Bus>
    void clockFast(Bus& bus) {
        clockImpl<false>(bus);
    }

private:
    // Tick the cpu, advancing its internal state and handling bus interactions.
    template <bool Capture, class Bus>
    void clockImpl(Bus& bus) {
        bus.tick();
        bus.setLock(locked_ || interrupt_lock_);
        bus.setPassiveOrHalt(t_state_ == TState::TIdle || halted_);
        const bool intr = bus.interruptPending();
        intr_line_ = intr;
        interruptPending = !interrupt_delay_ && (nmi_pending_ || (intr && (r[FLAGS] & IF) != 0));
        if (!single_instruction_ && !instructionStarted) {
            if (!interrupt_delay_) {
                if (nmi_pending_) {
                    nmi_pending_ = false;
                    beginInterrupt(0x7002);
                }
                else if (intr && (r[FLAGS] & IF)) {
                    beginInterrupt(0x7020);
                }
                else if (trap_pending_) {
                    beginInterrupt(0x7000);
                }
            }
            if (halted_ && intr) {
                // NEC standby can also be left by a masked INT without
                // acknowledging it; resume the instruction after HLT.
                halted_ = prefetch_suspended_ = false;
            }
        }
        queue_status_ = next_queue_status_;
        queue_byte_ = next_queue_byte_;
        next_queue_status_ = next_queue_byte_ = 0;

        // A completed fetch crosses the BIU/EU queue pipeline before the
        // decoder can consume it: T4 data becomes available on the next T2.
        if (prefetch_publish_delay_ && !--prefetch_publish_delay_) {
            publishPrefetch();
        }

        if (Capture) {
            pins = Cycle{};
            pins.lock = locked_ || interrupt_lock_;
            pins.bhe = bhe_pin_;
        }
        tickBiu<Capture>(bus);

        if (opr_latch_pending_ && read_count_) {
            latchOprFromRead();
        }

        if (flush_pending_) {
            if (flush_delay_) {
                --flush_delay_;
            }
            // Finish the old fetch through T4. If MW has missed the adjacent
            // transfer boundary, retain its two-clock arbitration interval.
            if (!flush_delay_ && !(t_state_ != TState::TIdle && bus_prefetch_) &&
                !(request_pending_ && bus_idle_clocks_ == 1)) {
                flush_pending_ = false;
                completePrefetchFlush(flush_ip_, flush_from_operand_, flush_from_alu_);
            }
        }

        if (!instructionDone && !halted_ && !executionStopped()) {
            tickEu<Capture>();
        }

        if (Capture) {
            pins.multiplexed = multiplexed_;
            pins.qs0 = (queue_status_ & 1) != 0;
            pins.qs1 = (queue_status_ & 2) != 0;
            pins.queueByte = queue_byte_;
        }

        if (!request_pending_) {
            request_write_accepted_ = false;
        }
        ++clocks;
    }

    Model model_;
    bool single_instruction_ = false, halted_ = false, mode_flag_writable_ = false;
    uint64_t instruction_count_ = 0;
    uint16_t instruction_start_ip_ = 0, instruction_start_cs_ = 0xffff;
    unsigned interrupt_delay_ = 0;
    bool interrupt_entry_ = false, instruction_native_ = true;
    bool intr_line_ = false, nmi_line_ = false, nmi_pending_ = false, trap_pending_ = false, instruction_trap_ = false;

    enum class Loader
    {
        Opcode,
        PrefixDelay,
        Modrm,
        DisplacementDelay,
        Displacement,
        EaDelay,
        EaRead,
        Execute,
        Finish,
        NextOpcode
    };

    enum class Eu
    {
        Running,
        SupplyingWriteData
    };

    enum class MicroState
    {
        Running,
        WaitingForQueueData,
        WaitingForOperand,
        WaitingForRequestSlot,
        WaitingForPrefetch
    };

    Loader loader_ = Loader::Opcode;
    Eu eu_ = Eu::Running;
    MicroState micro_state_ = MicroState::Running;
    bool micro_branch_delay_ = false;
    bool operand_busy_at_e_ = false;
    bool alu_repeat_delay_ = false;
    unsigned waiting_queue_bytes_ = 0;
    const InstructionInfo* decode_info_ = nullptr;
    bool extended_opcode_ = false, prefetch_suspended_ = false, locked_ = false;
    bool interrupt_lock_ = false;
    bool opr_valid_ = false, write_data_ready_ = false;
    bool opr_latch_pending_ = false;
    uint16_t write_data_ = 0;
    bool request_pending_ = false;
    bool request_write_accepted_ = false;
    unsigned request_delay_ = 0, request_reserve_delay_ = 0;

    struct BiuRequest
    {
        uint32_t base;
        uint16_t offset;
        uint8_t bytes, segment;
        bool write, io, inta = false;
    };

    BiuRequest active_request_{};
    BiuRequest queued_request_{};
    bool request_queued_ = false;
    unsigned queued_request_delay_ = 0;
    uint16_t queued_write_data_ = 0;
    bool queued_write_data_ready_ = false;
    bool queued_forward_read_ = false;
    bool vector_access_ = false;
    bool bus_inta_ = false;

    // Bus state
    bool bus_prefetch_ = false, bus_write_ = false, bus_io_ = false;
    bool bhe_pin_ = false;
    uint8_t repeat_prefix_ = 0, segment_override_ = 0xff, default_segment_ = DS;
    uint8_t displacement_bytes_ = 0, displacement_read_ = 0;
    uint8_t ea_delay_ = 0;
    bool displacement_stalled_ = false;
    bool ea_write_prepared_ = false;
    uint16_t displacement_ = 0, effective_address_ = 0, pfp_ = 0;
    unsigned prefetch_start_delay_ = 0, fetch_generation_ = 0, bus_generation_ = 0;
    unsigned suspend_delay_ = 0;
    bool fetch_blocked_ = false;
    bool fetch_restart_pending_ = false;
    bool write_waited_ = false;
    bool group_decode_delay_ = false;
    uint16_t pending_prefetch_data_ = 0;
    uint8_t pending_prefetch_bytes_ = 0, prefetch_publish_delay_ = 0;
    uint16_t next_micro_address_ = 0, last_micro_address_ = 0xffff;

    // ALU state
    Alu alu_operation_ = Alu::Add;
    Alu adjust_kind_ = Alu::Pass;
    bool adjust_carry_ = false, adjust_auxiliary_ = false;
    Reg alu_temporary_ = TA;
    bool alu_commit_flags_on_sigma_ = false;
    bool alu_zero_ = false;
    bool division_negative_ = false;
    int32_t division_high_ = 0;
    uint16_t alu_flags_ = 0, alu_flag_mask_ = 0;
    uint16_t alu_old_tmp_b_ = 0;
    bool absolute_negative_ = false, result_negative_ = false;

    // Prefetch queue
    std::array<uint8_t, 6> prefetch_queue_{};
    uint8_t queue_status_ = 0, queue_byte_ = 0;
    uint8_t next_queue_status_ = 0, next_queue_byte_ = 0;
    size_t prefetch_head_ = 0, prefetch_count_ = 0;

    TState t_state_ = TState::TIdle;
    uint8_t bus_bytes_ = 0, request_bytes_completed_ = 0, bus_segment_ = ES;
    uint8_t bus_idle_clocks_ = 0;
    uint64_t index_write_clock_ = 0;
    uint64_t opr_clock_ = 0;
    uint64_t cs_clock_ = 0;
    uint64_t pc_read_clock_ = uint64_t(-3);
    bool cs_transfer_pending_ = false;
    // Flushing stuff
    bool flush_pending_ = false;
    bool flush_from_operand_ = false;
    bool flush_from_alu_ = false;
    uint8_t flush_delay_ = 0;
    uint16_t flush_ip_ = 0;

    bool index_pending_ = false;
    uint32_t bus_address_ = 0, multiplexed_ = 0;
    uint16_t bus_value_ = 0, request_read_data_ = 0;

    std::array<uint16_t, 4> read_results_{};
    size_t read_head_ = 0, read_count_ = 0;

    // Insert a byte or word into the prefetch queue. Throws if the queue is full.
    void publishPrefetch() {
        for (unsigned lane = 0; lane < pending_prefetch_bytes_; ++lane) {
            enqueue(uint8_t(pending_prefetch_data_ >> (lane * 8)));
        }
        pending_prefetch_bytes_ = prefetch_publish_delay_ = 0;
    }

    // Insert a byte into the prefetch queue. Throws if the queue is full.
    void enqueue(uint8_t value) {
        if (prefetch_count_ >= queueCapacity()) {
            throw std::logic_error("queue overflow");
        }

        prefetch_queue_[(prefetch_head_ + prefetch_count_) % prefetch_queue_.size()] = value;
        ++prefetch_count_;
    }

    // Return the operand kind/register pair for the given index.
    Operand regOperand(unsigned index) const {
        // BINS/BEXT use byte registers for bit indexes and lengths even when
        // their microcode operates on a word.
        const bool byteRegister = decode_info_->isGroup(InstructionGroup::Bitfield);
        return {wordSize && !byteRegister ? Operand::Kind::Word : Operand::Kind::Byte, uint8_t(index)};
    }

    // Configure the operands for the current native instruction.
    void configureOperands() {
        wordSize = decode_info_->word;
        if (!instruction_native_) {
            configureEmulationOperands();
            return;
        }
        op1 = regOperand(decode_info_->accumulator ? 0 : opcode & 7);
        op2 = {Operand::Kind::Segment, uint8_t((opcode >> 3) & 3)};

        if (decode_info_->modrm) {
            op1 = (modrm & 0xc0) == 0xc0 ? regOperand(modrm & 7) : Operand{Operand::Kind::Memory, 0};
            op2 = decode_info_->segment ? Operand{Operand::Kind::Segment, uint8_t((modrm >> 3) & 3)}
                                        : regOperand((modrm >> 3) & 7);

            if (decode_info_->direction) {
                std::swap(op1, op2);
            }
        }

        const unsigned operation = ((opcode & 0x80 ? modrm : opcode) >> 3) & 7;
        decodedAluOperation = xiBanks[decode_info_->xiBank][operation];

        microAddress = decode_info_->entry;

        if (decode_info_->isGroup(InstructionGroup::ModrmEntry)) {
            microAddress = uint16_t((opcode & 8 ? 0x3000 : 0x2000) | (uint16_t(modrm) << 4));
            // These groups select their microcode entry from ModR/M through
            // an additional decode stage, rather than just selecting XI.
            group_decode_delay_ = true;
        }
        else if (!extended_opcode_ && repeat_prefix_) {
            microAddress |= 0x1000;
        }
    }

    // Begin EU execution for the current instruction.
    void startInstruction() {
        configureOperands();
        loader_ = Loader::Execute;
        if (!instruction_native_ && !extended_opcode_) {
            const bool memorySource = (opcode >= 0x40 && opcode < 0xc0 && (opcode & 7) == 6);
            const bool memoryIncrement =
                decode_info_->isGroup(InstructionGroup::IncDec) && op2.kind == Operand::Kind::Memory;
            if (memorySource || memoryIncrement) {
                writeIndex(r[BX]);
                requestRead(Segment::Default);
                loader_ = Loader::EaRead;
            }
        }
    }

    Operand emulationOperand(unsigned index) const {
        static constexpr uint8_t registers[] = {5, 1, 6, 2, 7, 3, 0, 0};
        return {index == 6 ? Operand::Kind::Memory : Operand::Kind::Byte, registers[index & 7]};
    }

    // Configure the operands for the current 8080 instruction.
    void configureEmulationOperands() {
        microAddress = decode_info_->entry;
        if (extended_opcode_) {
            return;
        }
        op1 = emulationOperand(opcode & 7);
        op2 = emulationOperand((opcode >> 3) & 7);
        // 8080 pairs BC/DE/HL/SP are CX/DX/BX/BP. SP remains the native
        // interrupt stack and is used by BRKEM, CALLN and RETEM microcode.
        const bool pair = (opcode < 0x40 && ((opcode & 7) == 1 || (opcode & 7) == 3 || (opcode & 0xe7) == 2)) ||
            (opcode & 0xcf) == 0xc1 || (opcode & 0xcf) == 0xc5;

        if (pair) {
            static constexpr uint8_t pairs[] = {1, 2, 3, 5};
            op2 = {Operand::Kind::Word, pairs[(opcode >> 4) & 3]};
        }

        static constexpr Alu arithmetic[] = {Alu::Add, Alu::Adc, Alu::Sub, Alu::Sbb,
                                             Alu::And, Alu::Xor, Alu::Or,  Alu::Cmp};
        decodedAluOperation = arithmetic[(opcode >> 3) & 7];

        if (opcode < 0x20 && (opcode & 7) == 7) {
            static constexpr Alu rotations[] = {Alu::Rol, Alu::Ror, Alu::Rcl, Alu::Rcr};
            decodedAluOperation = rotations[(opcode >> 3) & 3];
        }
        else if (opcode < 0x80 || ((opcode & 0xc7) != 0xc6 && opcode >= 0xc0)) {
            decodedAluOperation = Alu::Pass;
        }
    }

    // Prepare the effective address for the current instruction.
    void prepareEa() {
        const unsigned rm = modrm & 7, mode = modrm >> 6;
        default_segment_ = ((rm == 2 || rm == 3 || rm == 6) && !(mode == 0 && rm == 6)) ? SS : DS;
        const uint16_t bases[] = {uint16_t(r[BX] + r[SI]),
                                  uint16_t(r[BX] + r[DI]),
                                  uint16_t(r[BP] + r[SI]),
                                  uint16_t(r[BP] + r[DI]),
                                  r[SI],
                                  r[DI],
                                  r[BP],
                                  r[BX]};

        effective_address_ = mode == 0 && rm == 6 ? displacement_ : uint16_t(bases[rm] + displacement_);
        writeIndex(effective_address_);

        // EA hardware leaves the address available through SIGMA for LEA and
        // the far-pointer routines, before instruction microcode changes ALU setup.
        r[TA] = effective_address_;
        alu_operation_ = Alu::Pass;
        alu_temporary_ = TA;
        configureOperands();

        if (decode_info_->readEa) {
            requestTransfer(Segment::Default, false, 0);
            loader_ = Loader::EaRead;
        }
        else {
            if (decode_info_->writeEa) {
                // A direct OP2-to-OP1 store reserves the EA bus transaction
                // before microcode supplies its data, like an initial read.
                requestTransfer(Segment::Default, true, 0);
                ea_write_prepared_ = true;
            }
            loader_ = Loader::Execute;
        }
    }

    // Handle non-microcoded instructions implemented in miscellaneous logic.
    bool miscellaneous() {
        switch (decode_info_->groupOperation) {
            case 0: // ES:, CS:, SS:, DS: segment overrides
                segment_override_ = (opcode >> 3) & 3;
                break;
            case 1: // 0F extended-opcode prefix (native) / ED prefix (8080)
                extended_opcode_ = true;
                break;
            case 2: // STD
                r[FLAGS] |= DF;
                return false;
            case 3: // CLD
                r[FLAGS] &= ~DF;
                return false;
            case 4: // STI / EI (8080)
                r[FLAGS] |= IF;
                interrupt_delay_ = 2;
                return false;
            case 5: // CLI / DI (8080)
                r[FLAGS] &= ~IF;
                return false;
            case 6: // STC
                r[FLAGS] |= CF;
                return false;
            case 7: // CLC
                r[FLAGS] &= ~CF;
                return false;
            case 8: // REPC
            case 9: // REPNC
            case 12: // REP / REPE / REPZ
            case 13: // REPNE / REPNZ
                repeat_prefix_ = opcode;
                break;
            case 10: // CMC
                r[FLAGS] ^= CF;
                return false;
            case 11: // HLT
                halted_ = true;
                prefetch_suspended_ = true;
                retireInstruction();
                return false;
            case 14: // LOCK (F1 alias, tentative)
            case 15: // LOCK
                locked_ = true;
                break;
        }

        // Provisional two-bit saturation model, pending hardware validation.
        // Continue decoding prefixes after the restart count reaches its limit.
        if (prefixCount < 3) {
            ++prefixCount;
        }

        return true;
    }

    // Reset state for the next instruction, leaving the registers and flags intact.
    void clearInstructionState() {
        loader_ = Loader::Opcode;
        eu_ = Eu::Running;
        micro_state_ = MicroState::Running;
        decode_info_ = nullptr;
        extended_opcode_ = locked_ = vector_access_ = false;
        repeat_prefix_ = prefixCount = 0;
        segment_override_ = 0xff;
        default_segment_ = DS;
        endRequested = instructionStarted = false;
        operand_busy_at_e_ = false;
        ea_write_prepared_ = false;
        opr_valid_ = write_data_ready_ = false;
        opr_latch_pending_ = false;
        index_pending_ = false;
        read_count_ = read_head_ = 0;
        decodedAluOperation = Alu::Pass;
        // XLAT consumes the default ADD tmpA setup without an ALU micro-op.
        alu_operation_ = Alu::Add;
        alu_temporary_ = TA;
        alu_commit_flags_on_sigma_ = false;
    }

    // End EU execution of the currently executing instruction.
    void retireInstruction() {
        if (!interrupt_entry_) {
            ++instruction_count_;
            trap_pending_ = instruction_trap_;
        }
        if (interrupt_delay_) {
            --interrupt_delay_;
        }
        if (single_instruction_) {
            instructionDone = true;
            return;
        }
        clearInstructionState();
    }

    // Begin handling an interrupt with the specified entry point.
    void beginInterrupt(uint16_t entry) {
        // The selected model's INTA words feed the shared interrupt microcode.
        clearInstructionState();
        instruction_start_ip_ = r[IP];
        instruction_start_cs_ = r[CS];
        instructionStarted = interrupt_entry_ = true;
        instruction_native_ = true;
        instruction_trap_ = trap_pending_ = false;
        instructionDone = halted_ = false;
        prefetch_suspended_ = true;
        wordSize = true;
        microAddress = entry;
        loader_ = Loader::Execute;
    }

    // Request retirement of the current instruction if the EU is able to do so.
    void finishInstruction() {
        if (request_pending_ || flush_pending_) {
            return;
        }
        if (single_instruction_) {
            // Normal execution reaches the opcode loader on the next clock.
            // Keep the SST first-byte marker on that same clock.
            loader_ = Loader::NextOpcode;
            return;
        }
        retireInstruction();
    }

    // Execute one tick of the EU, handling microcode and instruction progression.
    template <bool Capture>
    void tickEu() {
        if (alu_repeat_delay_) {
            alu_repeat_delay_ = false;
            return;
        }
        if (micro_branch_delay_) {
            micro_branch_delay_ = false;
            return;
        }
        if (micro_state_ == MicroState::WaitingForQueueData) {
            if (microcodePrefetchBytes() < waiting_queue_bytes_) {
                return;
            }
        }
        if (micro_state_ == MicroState::WaitingForOperand && request_pending_ && !read_count_ &&
            !request_write_accepted_ && eu_ != Eu::SupplyingWriteData) {
            return;
        }
        if (micro_state_ == MicroState::WaitingForRequestSlot && request_queued_) {
            return;
        }

        write_waited_ = micro_state_ == MicroState::WaitingForOperand && request_write_accepted_;
        micro_state_ = MicroState::Running;

        switch (loader_) {
            case Loader::Opcode:
                if (!prefetch_count_ || queue_status_) {
                    return;
                }

                if (!instructionStarted) {
                    checkExecutionBreakpoint(r[CS], r[IP]);
                    if (executionStopped()) {
                        return;
                    }
                    instruction_start_ip_ = r[IP];
                    instruction_start_cs_ = r[CS];
                    instructionStarted = true;
                    instruction_native_ = nativeMode();
                    instruction_trap_ = instruction_native_ && (r[FLAGS] & TF) != 0;
                    interrupt_entry_ = false;
                }
                opcode = readQueue(!extended_opcode_);
                checkOpcode(opcode);
                decode_info_ = &opcodeDecodeTable[unsigned(opcode) + (extended_opcode_ ? 256 : 0) +
                                                  (instruction_native_ ? 0 : 512)];

                if (decode_info_->miscellaneous) {
                    if (!miscellaneous()) {
                        loader_ = Loader::Finish;
                    }
                    else {
                        loader_ = Loader::PrefixDelay;
                    }
                }
                else if (decode_info_->modrm) {
                    loader_ = Loader::Modrm;
                }
                else {
                    startInstruction();
                }
                return;

            case Loader::PrefixDelay:
                loader_ = Loader::Opcode;
                return;

            case Loader::Modrm:
                if (!prefetch_count_) {
                    return;
                }

                modrm = readQueue();

                if ((modrm & 0xc0) == 0xc0) {
                    // Register selection and the first microinstruction overlap.
                    startInstruction();
                    break;
                }
                else {
                    displacement_bytes_ = (modrm >> 6) == 1 ? 1 : ((modrm >> 6) == 2 || (modrm & 7) == 6 ? 2 : 0);
                    displacement_ = displacement_read_ = 0;
                    displacement_stalled_ = false;
                    loader_ = displacement_bytes_ == 1 ? Loader::DisplacementDelay : Loader::Displacement;

                    if (!displacement_bytes_) {
                        if (decode_info_->readEa || decode_info_->writeEa) {
                            // Initial operand transfers include BIU request setup.
                            ea_delay_ = 4;
                            loader_ = Loader::EaDelay;
                        }
                        else {
                            prepareEa();
                        }
                    }
                }
                return;

            case Loader::DisplacementDelay:
                // EA setup inserts a queue-idle clock before the last displacement
                // byte. If the queue is empty, that clock occurs after the queue is written.
                if (!prefetch_count_) {
                    displacement_stalled_ = true;
                    return;
                }
                loader_ = Loader::Displacement;
                return;

            case Loader::Displacement:
                if (!prefetch_count_) {
                    return;
                }

                displacement_ |= uint16_t(readQueue()) << (8 * displacement_read_++);

                if (displacement_read_ == displacement_bytes_) {
                    if (displacement_bytes_ == 1) {
                        displacement_ = extendByte(displacement_);
                    }

                    // The high-byte addition, or resuming a stalled byte load,
                    // occupies one more address-adder clock.
                    ea_delay_ = displacement_bytes_ == 2 || displacement_stalled_ ? 3 : 2;
                    if (!decode_info_->readEa && !decode_info_->writeEa) {
                        ea_delay_ -= 2;
                    }
                    if (ea_delay_) {
                        loader_ = Loader::EaDelay;
                    }
                    else {
                        prepareEa();
                        // A prefetched byte displacement can feed the first
                        // microinstruction in the same clock.
                        break;
                    }
                }
                else {
                    loader_ = Loader::DisplacementDelay;
                }
                return;

            case Loader::EaDelay:
                if (!--ea_delay_) {
                    prepareEa();
                }
                return;

            case Loader::EaRead:
                if (!request_pending_) {
                    latchOprFromRead();
                    loader_ = Loader::Execute;
                }
                return;

            case Loader::Finish:
                finishInstruction();
                return;

            case Loader::NextOpcode:
                if (!prefetch_count_ || queue_status_) {
                    return;
                }
                // Consume the boundary indication without executing the next
                // instruction or advancing the architectural IP past its opcode.
                readQueue(true);
                --r[IP];
                retireInstruction();
                return;

            case Loader::Execute:
                break;
        }

        if (group_decode_delay_) {
            group_decode_delay_ = false;
            return;
        }

        next_micro_address_ = (microAddress + 1) & 0x7fff;
        const bool retiring = endRequested;

        last_micro_address_ = microAddress;
        if (Capture) {
            pins.microcodePointer = microAddress;
        }
        executeMicrocode(microAddress);

        if (micro_state_ != MicroState::Running) {
            return;
        }

        ++microSteps;
        microAddress = next_micro_address_ & 0x7fff;

        if (!retiring && endRequested) {
            // E starts decode only if the operand bus was already free. A
            // final write's T4 cannot retroactively open that overlap window.
            operand_busy_at_e_ = request_pending_ || request_write_accepted_;
        }

        if (retiring) {
            const bool overlap_decode = !operand_busy_at_e_ && !request_pending_ && !request_write_accepted_ &&
                !queue_status_ && !next_queue_status_;

            loader_ = Loader::Finish;
            // When the final word coincides with write completion, retire the
            // instruction on the following clock. A pre-existing Finish wait
            // may resolve at T4; completing a microinstruction uses that EU clock.
            if (!request_write_accepted_) {
                finishInstruction();
            }
            // E starts the following instruction's decode while the final
            // microinstruction completes. A pending write cannot overlap it.
            const bool interrupt_boundary = !single_instruction_ && !interrupt_delay_ &&
                (nmi_pending_ || trap_pending_ || (intr_line_ && (r[FLAGS] & IF)));

            if (overlap_decode && !interrupt_boundary) {
                tickEu<Capture>();
            }
        }
    }

    void requestTransfer(Segment segment, bool write, unsigned delay = 2) {
        // A newly prepared address and write operand can cross to the BIU
        // before MW arrives. Data supplied on the MW word still needs the
        // ordinary setup delay, even when IND was prepared much earlier.
        if (delay == 2 && write && index_pending_ && clocks - index_write_clock_ >= 2 && opr_valid_ &&
            clocks - opr_clock_ >= 2) {
            --delay;
        }
        index_pending_ = false;
        const unsigned sr = segment == Segment::ES ? unsigned(ES)
            : segment == Segment::SS               ? unsigned(SS)
            : segment_override_ != 0xff            ? segment_override_
                                                   : default_segment_;
        const bool unsegmented = segment == Segment::Io;
        const BiuRequest request{unsegmented ? 0 : uint32_t(r[sr]) << 4, r[IND], uint8_t(wordSize ? 2 : 1),
                                 uint8_t(unsegmented ? 1 : sr),          write,  unsegmented && !vector_access_};

        if (request_pending_) {
            if (request_queued_) {
                unsupported("memory request queue overflow");
            }

            // A write-data pipeline can reach another request before T3.
            // Complete that microinstruction once and retain its address/data.
            // The EU may continue independent work.
            // F, request capacity, and instruction retirement synchronize it with the BIU as needed.
            queued_request_ = request;
            queued_request_delay_ = delay;
            queued_write_data_ = r[OPR];
            queued_write_data_ready_ = request.write && opr_valid_;
            queued_forward_read_ = request.write && !active_request_.write && !opr_valid_;
            if (request.write) {
                opr_valid_ = false;
            }
            request_queued_ = true;
            eu_ = Eu::Running;
            return;
        }

        beginRequest(request);

        // A request crosses the EU/BIU pipeline before it can win arbitration.
        // The first clock can still trigger a prefetch already selected by BIU.
        request_delay_ = delay;
        request_reserve_delay_ = request_delay_ ? request_delay_ - 1 : 0;
    }

    // Begin a bus request
    void beginRequest(const BiuRequest& request) {
        active_request_ = request;
        request_delay_ = request_reserve_delay_ = 0;
        request_write_accepted_ = false;
        request_bytes_completed_ = 0;
        request_read_data_ = 0;
        write_data_ready_ = false;

        request_pending_ = true;

        if (!request.write) {
            // Subsequent microinstructions run until an F word needs the data.
            eu_ = Eu::Running;
        }
        else if (opr_valid_) {
            supplyWriteData();
        }
        else {
            // Some words request a write before the following word supplies
            // OPR. Keep the EU running until that assignment or the bus data
            // phase, which can also reuse the retained OPR value.
            eu_ = Eu::SupplyingWriteData;
        }
    }

    void supplyWriteData() {
        write_data_ = r[OPR];
        write_data_ready_ = true;
        opr_valid_ = false;
        // The BIU retains this copy. Independent EU words can execute while
        // the write progresses; F and instruction retirement synchronize it.
        eu_ = Eu::Running;
    }

    bool eaReservesBus() const {
        // Initial operand transfers reserve the final two EA-delay clocks.
        if (loader_ != Loader::EaDelay || ea_delay_ > 2) {
            return false;
        }
        if (!decode_info_->readEa && !decode_info_->writeEa) {
            return false;
        }

        // A byte displacement read without a refill wait permits prefetch.
        return displacement_bytes_ != 1 || displacement_stalled_;
    }

    // Tick the Bus Interface Unit (BIU) for one clock cycle.
    template <bool Capture, class Bus>
    void tickBiu(Bus& bus) {
        // Handle various BIU stall conditions.
        if (suspend_delay_ && --suspend_delay_ <= 1) {
            prefetch_suspended_ = true;
        }
        const bool fetch_ready = prefetch_start_delay_ == 0;
        if (prefetch_start_delay_) {
            --prefetch_start_delay_;
        }
        const unsigned fetch_reserved = t_state_ >= TState::T3 && bus_prefetch_ ? bus_bytes_ : 0;
        if (fetch_ready && prefetch_count_ + pending_prefetch_bytes_ + fetch_reserved == queueCapacity()) {
            fetch_blocked_ = true;
        }
        if (request_queued_ && queued_request_delay_) {
            --queued_request_delay_;
        }
        const bool request_ready = request_delay_ == 0;
        // After a write, a pending write takes priority over refilling the
        // last queue slot even before its address pipeline has completed.
        const bool request_reserved = request_pending_ &&
            (request_delay_ <= request_reserve_delay_ ||
             (active_request_.write && bus_write_ && !bus_prefetch_ &&
              prefetch_count_ + pending_prefetch_bytes_ >= queueCapacity() - 1));

        if (request_delay_) {
            --request_delay_;
        }

        // Handle prefetch decision
        if (t_state_ == TState::TIdle) {
            if (request_pending_ && request_ready && bus_idle_clocks_ != 1) {
                // EU request pending, initiate bus cycle for it
                bus_prefetch_ = false;
                bus_write_ = active_request_.write;
                bus_io_ = active_request_.io;
                bus_address_ = (active_request_.base + uint16_t(active_request_.offset + request_bytes_completed_)) &
                    (bus_io_ ? 0xffff : 0xfffff);
                bus_bytes_ =
                    model_ == Model::V30 && !(bus_address_ & 1) && active_request_.bytes - request_bytes_completed_ >= 2
                    ? 2
                    : 1;
                bus_segment_ = active_request_.segment;

                bus_inta_ = active_request_.inta;
                t_state_ = TState::T1;
            }
            else if (fetch_ready && !prefetch_suspended_ && !request_reserved &&
                     prefetch_count_ + pending_prefetch_bytes_ < queueCapacity() && !eaReservesBus()) {
                // Prefetch qualified, initiate prefetch bus cycle
                bus_prefetch_ = true;
                bus_write_ = bus_io_ = bus_inta_ = false;
                bus_address_ = ((uint32_t(r[CS]) << 4) + pfp_) & 0xfffff;
                bus_bytes_ = model_ == Model::V30 && !(pfp_ & 1) &&
                        prefetch_count_ + pending_prefetch_bytes_ + 2 <= queueCapacity()
                    ? 2
                    : 1;
                bus_segment_ = CS;
                bus_generation_ = fetch_generation_;
                t_state_ = TState::T1;
            }
        }

        if (t_state_ == TState::TIdle) {
            // For some reason we didn't start a prefetch or bus cycle.
            // Once a request misses the back-to-back transfer boundary, the
            // BIU arbitration interval occupies two idle clocks.
            // I believe this is analagous to the 8088's t0 and tc cycles.
            if (bus_idle_clocks_ < 2) {
                ++bus_idle_clocks_;
            }
            return;
        }
        bus_idle_clocks_ = 0;

        // Present stable write data even while READY is low. The motherboard
        // may need it to finish data conversion before releasing READY.
        if ((t_state_ == TState::T3 || t_state_ == TState::TWait) && bus_write_) {
            if (!write_data_ready_) {
                supplyWriteData();
            }
            bus_value_ = uint16_t(write_data_ >> (request_bytes_completed_ * 8));
            bus.driveWriteData(bus_value_);
        }
        const bool ready = bus.ready();
        bhe_pin_ = model_ == Model::V30 && bus_bytes_ == 1 && !(bus_address_ & 1);
        static constexpr uint8_t segmentStatus[] = {0, 2, 1, 3};

        // Capture pins, if specified. This is expensive to do on every clock,
        // so it is only done when requested.
        if (Capture) {
            pins.t = t_state_;
            pins.ready = ready;
            pins.ale = t_state_ == TState::T1;
            pins.bhe = bhe_pin_;
            pins.address = bus_address_;
            pins.status = t_state_ <= TState::T2 ? (bus_inta_           ? 0
                                                        : bus_prefetch_ ? 4
                                                        : bus_io_       ? (bus_write_ ? 2 : 1)
                                                                        : (bus_write_ ? 6 : 5))
                                                 : 7;
            pins.segment = t_state_ == TState::T1 ? 4 : segmentStatus[bus_segment_];
            const uint8_t strobe = t_state_ == TState::T2               ? (bus_write_ ? 2 : 4)
                : (t_state_ == TState::T3 || t_state_ == TState::TWait) ? (bus_write_ ? 3 : 4)
                                                                        : 0;
            pins.memory = bus_io_ || bus_inta_ ? 0 : strobe;
            pins.io = bus_io_ || bus_inta_ ? strobe : 0;
        }

        // Execute current T-state
        if (t_state_ == TState::T1) {
            bus.startAccess(bus_address_, bus_bytes_, bus_prefetch_, bus_io_, bus_write_, bus_inta_);
            multiplexed_ = bus_address_;
        }
        else if (t_state_ == TState::T2) {
            if (bus_inta_) {
                // BUSLOCK spans T2 of the first INTA through T2 of the second.
                // Count physical cycles: V20 splits one request; V30 issues two.
                interrupt_lock_ = !interrupt_lock_;
                bus.setLock(locked_ || interrupt_lock_);
                if (Capture) {
                    pins.lock = locked_ || interrupt_lock_;
                }
            }
            multiplexed_ =
                (bus_address_ & 0xffff) | (uint32_t(segmentStatus[bus_segment_]) << 16) | (r[FLAGS] & IF ? 0x40000 : 0);

            if (bus_write_) {
                driveDataPins(uint16_t((write_data_ready_ ? write_data_ : r[OPR]) >> (request_bytes_completed_ * 8)));
                if (write_data_ready_) {
                    bus.driveWriteData(uint16_t(write_data_ >> (request_bytes_completed_ * 8)));
                }
            }
        }
        else if (t_state_ == TState::T3 || t_state_ == TState::TWait) {
            if (bus_write_) {
                driveDataPins(bus_value_);
            }
            if (!ready) {
                t_state_ = TState::TWait;
                return;
            }
            if (bus_write_) {
                bus.write(bus_address_, bus_value_, bus_bytes_, bus_io_, clocks);
                // The EU can proceed once the final write is accepted at T3;
                // the BIU retains its transfer state through T4.
                request_write_accepted_ = request_bytes_completed_ + bus_bytes_ == active_request_.bytes;
            }
            else if (bus_inta_) {
                bus_value_ = bus.acknowledge();
            }
            else {
                bus_value_ = bus.read(bus_address_, bus_bytes_, bus_prefetch_, bus_io_, clocks);
            }

            const uint16_t driven = driveDataPins(bus_value_);
            if (Capture) {
                pins.data = driven;
            }
        }

        if (t_state_ == TState::T4) {
            if (bus_prefetch_) {
                if (bus_generation_ == fetch_generation_) {
                    pending_prefetch_data_ = bus_value_;
                    pending_prefetch_bytes_ = bus_bytes_;
                    prefetch_publish_delay_ = 2;
                    pfp_ += bus_bytes_;
                    if (fetch_restart_pending_) {
                        fetch_restart_pending_ = false;
                        prefetch_start_delay_ = 3;
                    }
                }
            }
            else {
                if (!bus_write_) {
                    request_read_data_ |= uint16_t(bus_value_ << (request_bytes_completed_ * 8));
                }

                request_bytes_completed_ += bus_bytes_;

                if (request_bytes_completed_ == active_request_.bytes) {
                    if (!bus_write_) {
                        if (read_count_ == read_results_.size()) {
                            unsupported("memory result queue overflow");
                        }

                        read_results_[(read_head_ + read_count_) % read_results_.size()] = request_read_data_;
                        ++read_count_;
                    }

                    request_pending_ = false;

                    if (request_queued_) {
                        request_queued_ = false;
                        if (queued_forward_read_) {
                            // A following write can reserve the BIU before
                            // its source read returns (MOVS, INS and OUTS).
                            latchOprFromRead();
                            queued_write_data_ = r[OPR];
                            queued_write_data_ready_ = true;
                        }
                        beginRequest(queued_request_);
                        request_delay_ = queued_request_delay_;
                        request_reserve_delay_ = 1;

                        if (active_request_.write && queued_write_data_ready_) {
                            write_data_ = queued_write_data_;
                            write_data_ready_ = true;
                            opr_valid_ = false;
                            eu_ = Eu::Running;
                        }
                    }
                }
            }

            t_state_ = TState::TIdle;
        }
        else if (t_state_ == TState::T1) {
            t_state_ = TState::T2;
        }
        else if (t_state_ == TState::T2) {
            t_state_ = TState::T3;
        }
        else {
            // T3 or the final READY wait completes the data phase.
            t_state_ = TState::T4;
        }
    }

    // Drive the data pins with the specified value, taking into account the bus width and alignment.
    uint16_t driveDataPins(uint16_t value) {
        const unsigned shift = model_ == Model::V30 && (bus_address_ & 1) ? 8 : 0;
        const uint32_t mask = bus_bytes_ == 2 ? 0xffff : 0xffu << shift;
        const auto driven = uint16_t((uint32_t(value) << shift) & mask);

        multiplexed_ = (multiplexed_ & ~mask) | driven;
        return driven;
    }
};

} // namespace marty::nec

#undef MARTY_NEC_NOINLINE
