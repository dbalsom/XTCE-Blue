// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <optional>
#include "PrefetchQueue.h"
#include "cpu_types.h"
#include "execution_control.h"

#if defined(_MSC_VER)
#define MARTY_CPU_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define MARTY_CPU_FORCE_INLINE inline __attribute__((always_inline))
#else
#define MARTY_CPU_FORCE_INLINE inline
#endif

namespace marty::intel
{

using PrefetchQueue = ::cpu::PrefetchQueue<6>;

enum class QueueReadState
{
    NoOperation = 0,
    FirstByte = 1,
    Flush = 2,
    SubsequentByte = 3
};

// Concrete clocked EU, ALU, instruction loader, and model-selected BIU.
class GeneratedCpu final : public ::cpu::ExecutionControl
{
    friend struct AluTestAccess;

public:
    enum class Model
    {
        Intel8086,
        Intel8088
    };
    static const Model defaultModel;

    // Datapath operations selected by generated ALU setup.
    enum class AluOp : uint8_t
    {
        ADD = 0x00,
        OR = 0x01,
        ADC = 0x02,
        SBB = 0x03,
        AND = 0x04,
        SUBT = 0x05,
        XOR = 0x06,
        CMP = 0x07,
        ROL = 0x08,
        ROR = 0x09,
        LRCY = 0x0a,
        RRCY = 0x0b,
        SHL = 0x0c,
        SHR = 0x0d,
        SETMO = 0x0e,
        SAR = 0x0f,
        PASS = 0x10,
        XI = 0x11,
        DAA = 0x14,
        DAS = 0x15,
        AAA = 0x16,
        AAS = 0x17,
        INC = 0x18,
        DEC = 0x19,
        COM1 = 0x1a,
        NEG = 0x1b,
        INC2 = 0x1c,
        DEC2 = 0x1d,
    };

    // Offsets from tmpa's slot in registers_.
    enum class AluInput : uint8_t
    {
        TmpA = 0,
        TmpB = 1,
        TmpC = 2
    };
    enum class Segment : uint8_t
    {
        ES = 0,
        CS = 1,
        SS = 2,
        DS = 3
    };

    enum GroupDecodeFlags : uint32_t
    {
        groupInitialEARead = 0x02,
        groupMicrocodePointerFromOpcode = 0x04,
        groupEffectiveAddress = 0x10,
        groupAddSubBooleanRotate = 0x20,
        groupMNotAccumulator = 0x80,
        groupNonSegregEA = 0x100,
        groupNoDirectionBit = 0x200,
        groupF1ZZFromPrefix = 0x2000,
        groupLoadRegisterImmediate = 0x10000,
        groupWidthInOpcodeBit3 = 0x20000,
    };

    enum MicrocodeState
    {
        stateRunning,
        stateWaitingForQueueData,
        stateSingleCycleWait
    };

    uint16_t registers_[32]{};
    uint32_t group_ = 0;
    uint8_t opcode_ = 0, mod_rm_ = 0;
    AluOp alu_ = AluOp::ADD;
    AluInput alu_input_ = AluInput::TmpA;
    bool carry_latch_ = false, nx_ = false;
    bool f1_ = false, repne_ = false, super_zero_ = false;
    bool test_pin_ = true, interrupt_pending_ = false;
    int counter_ = 0;
    bool rni_ = false, in_instruction_ = false;
    bool word_size_ = true, m_is_m_ = true, use_memory_ = false, skip_rni_ = false;

    // Selected by the instruction loader, or supplied by a low-level host.
    Segment segment_ = Segment::DS;
    std::optional<Segment> segment_override_;
    uint16_t microcode_pointer_ = 0;
    uint16_t microcode_return_ = 0;
    MicrocodeState state_ = stateRunning;
    std::size_t queue_bytes_ = 0;

    explicit GeneratedCpu(Model model = defaultModel) :
        model_(model), microcode_methods_(imageFor(model).methods), intr_entry_(imageFor(model).intrEntry) {
        sr(1) = 0xffff;
        registers_[21] = 0xffff;
        flags() = 0xf002;
        group_ = 8;
    }

    void reset() {
        const auto controls = static_cast<const ::cpu::ExecutionControl&>(*this);
        *this = GeneratedCpu(model_);
        static_cast<::cpu::ExecutionControl&>(*this) = controls;
        resetExecutionControl();
    }

    // rw(): read-register-word
    // Return a reference to the register for the given register index, relative
    // to the base of the general-purpose registers.
    uint16_t& rw(const int r) { return registers_[24 + r]; }

    // rw(): read-register-word
    // Return a reference to the register for the given register index, relative
    // to the base of the general-purpose registers, using the current opcode's
    // low 3 bits.
    uint16_t& rw() { return rw(opcode_ & 7); }

    // Return a reference to the accumulator register.
    uint16_t& ax() { return rw(0); }

    // rb(): read-register-byte
    // Return a reference to the byte for the given register index, relative
    // to the base of the general-purpose registers. Handles endianness.
    uint8_t& rb(const int r) {
        // Compute the byte reference on demand so copied CPUs never retain
        // pointers into another instance's register array. Also handles BE hosts.
        constexpr uint16_t endian = 1;
        const bool little = *reinterpret_cast<const uint8_t*>(&endian) != 0;

        return reinterpret_cast<uint8_t*>(&rw(r & 3))[(r >> 2) ^ !little];
    }

    // Return a reference to the low byte of the accumulator register.
    uint8_t& al() { return rb(0); }

    // Return a reference to the stack register (SR).
    uint16_t& sr(int r) { return registers_[r & 3]; }

    // Return a reference to the program counter (PC) register.
    uint16_t& pc() { return registers_[4]; }

    // Return a reference to the indirect register (IND).
    uint16_t& ind() { return registers_[5]; }

    // Return a reference to the operand register (OPR).
    uint16_t& opr() { return registers_[6]; }

    // Return a reference to the temporary register A (TMPA).
    uint16_t& tmpa() { return registers_[12]; }

    // Return a reference to the temporary register B (TMPB).
    uint16_t& tmpb() { return registers_[13]; }

    // Return a reference to the temporary register C (TMPC).
    uint16_t& tmpc() { return registers_[14]; }

    // Return a reference to the flags register (FLAGS).
    uint16_t& flags() { return registers_[15]; }

    // CY/NCY observe the internal ALU carry, independently of FLAGS.CF and
    // the carry write-enable latch.
    bool getAluCF() const { return carry_; }

    // Return the register index for the ModR/M 'reg' field.
    int modRMReg() const { return (mod_rm_ >> 3) & 7; }

    // Return the register index for the ModR/M 'r/m' field.
    int modRMReg2() const { return mod_rm_ & 7; }

    // Get the value from memory or register based on the ModR/M byte and the 'mem' flag.
    uint16_t getMemOrReg(bool mem) {
        if (mem) {
            if (use_memory_) {
                return opr();
            }

            if (!word_size_) {
                return rb(modRMReg2());
            }

            return rw(modRMReg2());
        }

        if ((group_ & groupNonSegregEA) == 0) {
            return sr(modRMReg());
        }

        if (!word_size_) {
            const int n = modRMReg();
            const uint16_t value = rw(n & 3);

            // xtce_blue preserves the other byte on this source path.
            return (n & 4) != 0 ? uint16_t((value >> 8) | (value << 8)) : value;
        }

        return rw(modRMReg());
    }

    // Set the value in memory or register based on the ModR/M byte and the 'mem' flag.
    void setMemOrReg(bool mem, uint16_t value) {
        if (mem) {
            if (use_memory_) {
                opr() = value;
            }
            else if (!word_size_) {
                rb(modRMReg2()) = static_cast<uint8_t>(value);
            }
            else {
                rw(modRMReg2()) = value;
            }
        }
        else {
            if ((group_ & groupNonSegregEA) == 0) {
                sr(modRMReg()) = value;
            }
            else if (!word_size_) {
                rb(modRMReg()) = static_cast<uint8_t>(value);
            }
            else {
                rw(modRMReg()) = value;
            }
        }
    }

    // Read the 'M' microcode operand, which may be a register or memory based on the ModR/M byte.
    uint16_t mc_read_m() {
        if ((group_ & groupMNotAccumulator) == 0) {
            // The 8086 drives both data lanes on byte writes, including AH.
            return (word_size_ || is8086()) ? ax() : al();
        }

        if ((group_ & groupEffectiveAddress) == 0) {
            return rw();
        }

        return getMemOrReg(m_is_m_);
    }

    // Read the 'R' microcode operand, which may be a register or memory based on the ModR/M byte.
    uint16_t mc_read_r() {
        if ((group_ & groupEffectiveAddress) == 0) {
            return sr((opcode_ >> 3) & 7);
        }

        return getMemOrReg(!m_is_m_);
    }

    // Write to the 'M' microcode operand, which may be a register or memory based on the ModR/M byte.
    void mc_write_m(uint32_t value) {
        if (alu_ == AluOp::CMP) {
            // CMP computes flags without writing back to M.
            return;
        }

        if ((group_ & groupMNotAccumulator) == 0) {
            if (word_size_) {
                ax() = value;
            }
            else {
                al() = static_cast<uint8_t>(value);
            }

            return;
        }

        if ((group_ & groupEffectiveAddress) == 0) {
            if (((group_ & groupLoadRegisterImmediate) != 0 && (opcode_ & 8) == 0) ||
                ((group_ & groupWidthInOpcodeBit3) != 0 && (opcode_ & 8) != 0)) {
                rb(opcode_ & 7) = static_cast<uint8_t>(value);
            }
            else {
                rw() = value;
            }
        }
        else {
            setMemOrReg(m_is_m_, value);
            skip_rni_ = m_is_m_ && use_memory_;
        }
    }

    // Write to the 'R' microcode operand, which may be a register or memory based on the ModR/M byte.
    void mc_write_r(uint32_t value) {
        if ((group_ & groupEffectiveAddress) == 0) {
            sr((opcode_ >> 3) & 7) = value;
        }
        else {
            setMemOrReg(!m_is_m_, value);
        }
    }

    // Accept architectural instruction state from the loader or low-level host.
    void configure_instruction(uint8_t opcode, uint8_t modrm, uint32_t group, bool word_size) {
        opcode_ = opcode;
        mod_rm_ = modrm;
        group_ = group;
        word_size_ = word_size;
        m_is_m_ = (group & groupNoDirectionBit) != 0 || (opcode & 2) == 0;
        use_memory_ = (group & groupEffectiveAddress) != 0 && (modrm & 0xc0) != 0xc0;
        skip_rni_ = false;
        alu_ = AluOp::ADD;
        alu_input_ = AluInput::TmpA;
        carry_latch_ = false;
        nx_ = false;
        readFlags();
    }

    // Dense switch IDs defined in the generated tables for the selected CPU ROM.
    using MicrocodeId = uint16_t;
    static constexpr MicrocodeId invalidMethod = 0xffff;

    struct DispatchEntry
    {
        MicrocodeId method;
        uint16_t next;
        bool mapped;
    };

    struct InstructionEntry
    {
        uint32_t group;
        bool word, extensionDelay;
        uint16_t entry[8];
    };

    // Generator-resolved EA routine address and its default segment.
    struct EffectiveAddressEntry
    {
        uint16_t startAddress;
        Segment segment;
    };

    // Generator-resolved ROM column for each 11-bit PLA input; 0xff is unmapped.
    static const uint8_t mc_columns[2048];
    static const InstructionEntry mc_instruction_table[256];
    static const uint32_t interruptGroup;
    static const EffectiveAddressEntry mc_ea_table[256];
    static const MicrocodeId mc_8086_dispatch_ids[512];
    static const MicrocodeId mc_8088_dispatch_ids[512];
    static const char* const mc_8086_disassembly[512];
    static const char* const mc_8088_disassembly[512];

    // Resolve a logical microcode pointer to a preformatted physical ROM word.
    // This is only called by tracing; normal execution keeps using dispatch IDs.
    static const char* microcodeDisassembly(uint16_t address, Model model) {
        if (address >= 8192 || unsigned(model) >= 2) {
            return nullptr;
        }
        const uint8_t column = mc_columns[address >> 2];
        if (column == 0xff) {
            return nullptr;
        }
        const auto* descriptions = model == Model::Intel8086 ? mc_8086_disassembly : mc_8088_disassembly;
        return descriptions[column * 4 + (address & 3)];
    }

    struct Image
    {
        const MicrocodeId* methods;
        uint16_t intrEntry;
    };

    static const Image mc_images[2];

    static const Image& imageFor(Model model) {
        assert(unsigned(model) < 2 && mc_images[unsigned(model)].methods && "CPU model absent from generated image");

        return mc_images[unsigned(model)];
    }

    Model model_;
    const MicrocodeId* microcode_methods_;
    uint16_t intr_entry_;

    bool is8086() const { return model_ == Model::Intel8086; }

    // Cached column selection and word offset; no runtime PLA or word decoding.
    static DispatchEntry resolveDispatch(uint16_t address, const MicrocodeId* methods) {
        if (address >= 8192) {
            return {invalidMethod, 0, false};
        }

        const uint8_t column = mc_columns[address >> 2];
        const uint16_t next = (address & 0x1ff0) | ((address + 1) & 15);

        if (column == 0xff) {
            return {invalidMethod, next, false};
        }

        return {methods[column * 4 + (address & 3)], next, true};
    }


    // Declarations cover all ROM slots; only occupied slots are defined by
    // the generator. Synthetic ROM tests can populate any of these slots.

    static constexpr uint32_t groupMemory = 1, groupIncDec = 0x4000;

    uint32_t physical(unsigned segment, uint16_t offset) { return ((uint32_t(sr(segment)) << 4) + offset) & 0xfffff; }

    void setInternalCarry(bool value) { carry_ = value; }

    uint16_t doALU() { return calculateALU(); }

    template <AluOp Op, AluInput Input>
    MARTY_CPU_FORCE_INLINE uint16_t doALUFixed() {
        assert(alu_ == Op && alu_input_ == Input && "invalid static ALU specialization");
        return calculateALU<true, Op, Input>();
    }

    bool cf() { return flags() & 1; }

    bool pf() { return flags() & 4; }

    bool af() { return flags() & 0x10; }

    bool zf() { return flags() & 0x40; }

    bool sf() { return flags() & 0x80; }

    bool of() { return flags() & 0x800; }

    bool df() { return flags() & 0x400; }

    void setAluCF(bool value) {
        if (carry_latch_ && !(group_ & groupIncDec)) {
            carry_ = value;
        }
    }

private:
    bool carry_ = false, overflow_ = false, sign_ = false, zero_ = false, auxiliary_ = false;
    unsigned parity_ = 0;

    void readFlags() {
        carry_ = cf();
        overflow_ = of();
        parity_ = pf() ? 0x04 : 0;
        sign_ = sf();
        zero_ = zf();
        auxiliary_ = af();
    }

    uint16_t doRotate(uint16_t v, uint16_t a, bool carry) {
        carry_ = carry;
        overflow_ = topBit(v ^ a);

        return v;
    }

    uint16_t doShift(uint16_t v, uint16_t a, bool carry, bool auxiliary) {
        auxiliary_ = auxiliary;
        doPZS(v);

        return doRotate(v, a, carry);
    }

    uint16_t doPass(uint16_t v) {
        auxiliary_ = false;
        doPZS(v);

        return v;
    }

    uint16_t doSetmo() {
        carry_ = false;
        overflow_ = false;
        auxiliary_ = false;
        doPZS(0xFFFF);

        return 0xFFFF;
    }

    uint16_t shiftRight(uint16_t value, bool incoming) const {
        if (!is8086()) {
            return ((value & wordMask()) >> 1) | topBit(incoming);
        }

        // A byte operation cuts the carry between the lanes, but still shifts
        // the upper lane. Both lane inputs receive the selected incoming bit.
        return ((value >> 1) & (word_size_ ? 0xffff : 0xff7f)) | (incoming ? (word_size_ ? 0x8000 : 0x8080) : 0);
    }

    template <bool Fixed = false, AluOp Op = AluOp::ADD, AluInput Input = AluInput::TmpA>
    uint16_t calculateALU() {
        const auto operation = Fixed ? Op : alu_;
        const auto input = Fixed ? Input : alu_input_;
        uint32_t a = registers_[static_cast<int>(input) + 12], v = 0;

        switch (operation) {
            case AluOp::ADD: // ADD
            case AluOp::ADC: // ADC
                return add(a, tmpb(), carry_ && operation != AluOp::ADD);

            case AluOp::OR: // OR
                return bitwise(a | tmpb());

            case AluOp::SBB: // SBB
            case AluOp::SUBT: // SUBT
            case AluOp::CMP: // CMP
                return sub(a, tmpb(), carry_ && operation == AluOp::SBB);

            case AluOp::AND: // AND
                return bitwise(a & tmpb());

            case AluOp::XOR: // XOR
                return bitwise(a ^ tmpb());

            case AluOp::ROL: // ROL
                return doRotate((a << 1) | (topBit(a) ? 1 : 0), a, topBit(a));

            case AluOp::ROR: // ROR
                return doRotate(shiftRight(a, lowBit(a)), a, lowBit(a));

            case AluOp::LRCY: // LRCY
                return doRotate((a << 1) | (carry_ ? 1 : 0), a, topBit(a));

            case AluOp::RRCY: // RRCY
                return doRotate(shiftRight(a, carry_), a, lowBit(a));

            case AluOp::SHL: // SHL
                return doShift(a << 1, a, topBit(a), (a & 0x08) != 0);

            case AluOp::SHR: // SHR
                return doShift(shiftRight(a, false), a, lowBit(a), false);

            case AluOp::SETMO: // SETMO
                return doSetmo();

            case AluOp::SAR: // SAR
                return doShift(shiftRight(a, topBit(a)), a, lowBit(a), false);

            case AluOp::PASS: // PASS
                return doPass(a);

            case AluOp::DAA: // DAA
                {
                    const auto al = static_cast<uint8_t>(a);
                    const bool low_gt9 = (al & 0x0f) > 9;

                    // Calculate CF before modifying AF.
                    carry_ = carry_ || (al >> 4) > 9 || ((al >> 4) == 9 && low_gt9 && !auxiliary_);
                    auxiliary_ = auxiliary_ || low_gt9;

                    v = (al + (auxiliary_ ? 0x06 : 0) + (carry_ ? 0x60 : 0)) & 0xff;
                    overflow_ = (~al & v & 0x80) != 0;
                    doPZS(v);
                    break;
                }

            case AluOp::DAS: // DAS
                carry_ = carry_ || a > (auxiliary_ ? 0x9fU : 0x99U);
                auxiliary_ = auxiliary_ || (a & 0x0f) > 9;

                v = a - (auxiliary_ ? 0x06 : 0) - (carry_ ? 0x60 : 0);
                overflow_ = (a & ~v & 0x80) != 0;
                doPZS(v);
                break;

            case AluOp::AAA: // AAA
                carry_ = (auxiliary_ || (a & 0xf) > 9);
                auxiliary_ = carry_;
                v = a + (carry_ ? 6 : 0);
                overflow_ = (~a & v & 0x80) != 0;
                doPZS(v);

                return v & 0x0f;

            case AluOp::AAS: // AAS
                carry_ = (auxiliary_ || (a & 0xf) > 9);
                auxiliary_ = carry_;
                v = a - (carry_ ? 6 : 0);
                overflow_ = (a & ~v & 0x80) != 0;
                doPZS(v);

                return v & 0x0f;

            case AluOp::INC: // INC
                v = a + 1;
                doPZS(v);
                overflow_ = topBit((v ^ a) & (v ^ 1));
                auxiliary_ = (((v ^ a ^ 1) & 0x10) != 0);
                break;

            case AluOp::DEC: // DEC
                v = a - 1;
                doPZS(v);
                overflow_ = topBit((a ^ 1) & (v ^ a));
                auxiliary_ = (((v ^ a ^ 1) & 0x10) != 0);
                break;

            case AluOp::COM1: // COM1
                carry_ = false;
                overflow_ = false;

                return ~a;

            case AluOp::NEG: // NEG
                return sub(0, a, false);

            case AluOp::INC2: // INC2
                return a + 2; // flags never updated

            case AluOp::DEC2: // DEC2
                return a - 2; // flags never updated

            case AluOp::XI:
                assert(false && "XI must be resolved by generated code before using the ALU");
                break;
        }

        return v;
    }

    void updateFlags() {
        flags() = (flags() & 0xf702) | (overflow_ ? 0x800 : 0) | (sign_ ? 0x80 : 0) | (zero_ ? 0x40 : 0) |
            (auxiliary_ ? 0x10 : 0) | parity_ // Already shifted
            | (carry_ ? 1 : 0);
    }

    uint16_t wordMask() const { return word_size_ ? 0xffff : 0xff; }

    void doPZS(const uint16_t v) {
        static uint8_t table[0x100] = {
            4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
            0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
            0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
            4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
            0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4,
            4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
            4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0,
            0, 4, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 4, 0, 4, 0, 0, 4};
        parity_ = table[v & 0xff];
        zero_ = ((v & wordMask()) == 0);
        super_zero_ = (v == 0);
        sign_ = topBit(v);
    }

    void doFlags(const uint32_t result, const bool of, const bool af) {
        doPZS(result);
        overflow_ = of;
        auxiliary_ = af;
    }

    uint16_t bitwise(const uint16_t data) {
        doFlags(data, false, false);
        carry_ = false;

        return data;
    }

    void doAddSubFlags(const uint32_t result, const uint32_t x, const bool of, const bool af) {
        doFlags(result, of, af);
        setAluCF(((result ^ x) & (word_size_ ? 0x10000 : 0x100)) != 0);
    }

    static bool lowBit(uint32_t v) { return (v & 1) != 0; }

    bool topBit(const int w) const { return (w & (word_size_ ? 0x8000 : 0x80)) != 0; }

    bool topBit(const uint32_t w) const { return (w & (word_size_ ? 0x8000 : 0x80)) != 0; }

    uint16_t topBit(const bool v) const { return v ? (word_size_ ? 0x8000 : 0x80) : 0; }

    uint16_t add(const uint32_t a, const uint32_t b, const bool c) {
        const uint32_t r = a + b + (c ? 1 : 0);
        doAddSubFlags(r, a ^ b, topBit((r ^ a) & (r ^ b)), ((a ^ b ^ r) & 0x10) != 0);

        return r;
    }

    uint16_t sub(const uint32_t a, const uint32_t b, const bool c) {
        const uint32_t r = a - (b + (c ? 1 : 0));
        doAddSubFlags(r, a ^ b, topBit((a ^ b) & (r ^ a)), ((a ^ b ^ r) & 0x10) != 0);

        return r;
    }

public:
    struct Cycle
    {
        uint32_t address = 0;
        uint8_t segment = 0, memory = 0, io = 0;
        uint16_t data = 0;
        uint8_t status = static_cast<uint8_t>(BusStatus::Passive), queueByte = 0;
        TState t = TState::TIdle;
        bool ale = false, lock = false, qs0 = false, qs1 = false, bhe = false;
        int16_t microcodePointer = -1;
        int8_t loggerStatus = -1;
        TState nextBus = TState::TIdle;
        uint8_t nextIoType = static_cast<uint8_t>(BusStatus::Passive);
        bool ready = true, interruptFlag = false;

        uint8_t queueStatus() const { return uint8_t(qs0) | (uint8_t(qs1) << 1); }
    };

    PrefetchQueue queue;

    // Maximum-mode queue status outputs, latched once per clock. QS1:QS0 is
    // 00 idle, 01 first opcode byte, 10 queue flush, 11 subsequent byte.
    bool qs0() const { return qs0_pin_; }

    bool qs1() const { return qs1_pin_; }

    uint8_t queueStatus() const { return uint8_t(qs0_pin_) | (uint8_t(qs1_pin_) << 1); }
    uint8_t queueByte() const { return queue_byte_pin_; }

    // Like the interpreted core, execute clocks and test stop flags directly.
    template <class Host>
    uint64_t runFor(Host& host, uint64_t clocks) {
        beginRun();
        for (uint64_t n = 0; n < clocks; ++n) {
            clock(host);
            if (executionStopped()) {
                return n + 1;
            }
        }
        return clocks;
    }

    template <class Iterator>
    void setPrefetchQueue(Iterator first, Iterator last) {
        assert(cycle_count_ == 0 && "prefetch initialization requires a reset CPU");
        queue.assign(first, last, pc());
        assert(queue.size() <= (is8086() ? 6u : 4u) && "prefetch queue exceeds model capacity");
        queue_bytes_ = queue.size();
        pc() += uint16_t(queue.size());
        queue_filled_ = queue.size() >= (is8086() ? 5u : 4u);
    }

    uint64_t cycleCount() const { return cycle_count_; }
    uint64_t instructionCount() const { return instruction_count_; }
    uint16_t instructionPointer() const { return instruction_ip_; }
    uint16_t instructionSegment() const { return instruction_cs_; }
    uint16_t nextInstructionPointer() const { return next_ip_; }
    uint16_t nextInstructionSegment() const { return next_cs_; }
    bool instructionBoundary() const { return next_instruction_; }
    bool overlappingInstruction() const { return loader_ == 3; }
    bool halted() const { return eu_ == Halted; }
    void setNmiLine(bool level) {
        nmi_pending_ |= level && !nmi_line_;
        nmi_line_ = level;
    }
    void setTestPin(bool level) { test_pin_ = level; }
    const char* executionState() const {
        if (eu_ == Halted) {
            return "Halted";
        }
        if (eu_ >= HaltingStart) {
            return "Halting";
        }
        if (eu_ == Suspend) {
            return "Suspending";
        }
        if (eu_ == CorrectPC) {
            return "Correcting PC";
        }
        if (eu_ != Running) {
            return "Bus transfer";
        }
        if (state_ == stateWaitingForQueueData) {
            return "Waiting for queue data";
        }
        if (state_ == stateSingleCycleWait) {
            return "Single cycle wait";
        }
        return "Running";
    }

    uint8_t queueRead(QueueReadState kind) {
        // Callers stall on an empty queue before attempting a read.
        assert(!queue.empty());

        uint8_t value = queue.front();
        if (kind == QueueReadState::SubsequentByte && in_instruction_) {
            checkSoftwareInterrupt(opcode_, value);
        }
        queue.pop_front();
        dequeueing_ = true;
        next_queue_status_ = kind;
        next_queue_byte_ = value;
        last_queue_byte_ = value;

        return value;
    }

    void startWriteRniDDP0() { mc_bus(true, false, true, 3, 3); }

    void mc_bus(bool write, bool iak, bool rni, uint8_t segment, uint8_t factor) {
        // A prefetch entering address preparation can be canceled by an EU
        // request. Its T1/ALE is suppressed, but byte selection still reaches
        // BHE two clocks later. A fetch already prepared retains word width.
        aborted_prefetch_ = is8086() && bus_ == TState::TIdle && canPrefetch();
        request_ = {write, iak, rni, segment, factor};
        eu_ = IODelay1;

        if (bus_ == TState::T3 || bus_ == TState::TWait || canPrefetch()) {
            eu_ = IODelay2;
        }

        if (bus_ == TState::T4 || bus_ == TState::TIdle) {
            bus_status_ = BusStatus::Passive;
        }

        io_requested_ = true;
    }

    void flushQueue() {
        queue.clear();
        queue_bytes_ = 0;
        next_queue_status_ = QueueReadState::Flush;
        next_queue_byte_ = last_queue_byte_;
        flushing_ = true;
    }

    void correctPC() { eu_ = CorrectPC; }

    void suspendPrefetch() {
        prefetching_ = false;

        if (bus_ != TState::T4 && bus_ != TState::TIdle) {
            eu_ = Suspend;
        }
        else {
            bus_status_ = BusStatus::Passive;
        }
    }

private:
    TState bus_ = TState::TIdle;

    enum EU
    {
        Running,
        IODelay2,
        IODelay1,
        FirstStart,
        FirstDone,
        SecondDone,
        CorrectPC,
        Suspend,
        HaltingStart,
        Halting3,
        Halting2,
        Halting1,
        Halted
    } eu_ = Running;

    BusStatus bus_status_ = BusStatus::Passive, last_bus_status_ = BusStatus::Passive;
    int io_segment_ = 1;
    uint32_t io_address_ = 0, address_bus_ = 0;
    uint16_t io_index_ = 0;
    uint16_t io_read_ = 0, io_write_ = 0, committed_write_ = 0;
    bool bus_word_ = false, last_bus_word_ = false, bhe_pin_ = false, aborted_prefetch_ = false;

    struct BusRequest
    {
        bool write = false, acknowledge = false, complete = false;
        uint8_t segment = 0, indexUpdate = 0;
    } request_;

    bool io_requested_ = false, prefetching_ = true, flushing_ = false;
    bool t4_ = false, t5_ = false, t6_ = false, queue_filled_ = false, dequeueing_ = false;
    bool lock_ = false, locking_ = false, read_prefix_ = false;
    bool started_ = false, next_instruction_ = false;
    bool ready_ = true, intr_line_ = false, nmi_line_ = false, nmi_pending_ = false;
    bool boundary_checked_ = false, trap_ = false, intr_shadow_ = false, all_shadow_ = false;
    bool inhibit_intr_ = false, inhibit_all_ = false;
    bool extra_halt_delay_ = false;
    uint16_t interrupt_entry_ = 0;
    uint64_t cycle_count_ = 0, instruction_count_ = 0;
    uint16_t instruction_ip_ = 0, instruction_cs_ = 0xffff, next_ip_ = 0, next_cs_ = 0xffff;
    QueueReadState next_queue_status_ = QueueReadState::NoOperation;
    bool qs0_pin_ = false, qs1_pin_ = false;
    uint8_t next_queue_byte_ = 0, last_queue_byte_ = 0, queue_byte_pin_ = 0;
    int loader_ = 0;
    uint8_t next_opcode_ = 0;
    uint32_t next_group_ = 0;
    MicrocodeId pending_ = invalidMethod;

    bool canPrefetch() const {
        return prefetching_ && !io_requested_ && bus_status_ == BusStatus::Passive && !t4_ && !queue_filled_;
    }

    void readOpcode(int nextLoader) {
        if (!read_prefix_) {
            if (!boundary_checked_) {
                inhibit_intr_ = intr_shadow_;
                inhibit_all_ = all_shadow_;
                intr_shadow_ = all_shadow_ = false;
                boundary_checked_ = true;
            }
            uint16_t entry = 0;
            if (!inhibit_all_) {
                if (nmi_pending_) {
                    nmi_pending_ = false;
                    entry = 0x1001;
                }
                else if (!inhibit_intr_ && intr_line_ && (flags() & 0x200)) {
                    entry = 0x1002;
                }
                else if (trap_) {
                    entry = 0x1000;
                }
            }
            if (entry) {
                interrupt_entry_ = entry;
                loader_ = nextLoader | 1;
                return;
            }
        }
        if (queue_bytes_) {
            next_ip_ = uint16_t(pc() - queue_bytes_);
            next_cs_ = sr(1);
            if (!read_prefix_) {
                next_instruction_ = true;
            }
            started_ = true;
            next_opcode_ = queueRead(QueueReadState::FirstByte);
            next_group_ = mc_instruction_table[next_opcode_].group;
            loader_ = nextLoader | 1;
        }
        else {
            loader_ = nextLoader & 2;
        }
    }

    void startInstruction() {
        if (group_ & 8) {
            segment_override_.reset();
            f1_ = false;
            repne_ = false;
            lock_ = false;
        }

        if (!read_prefix_) {
            instruction_ip_ = next_ip_;
            instruction_cs_ = next_cs_;
        }
        checkOpcode(next_opcode_);
        opcode_ = next_opcode_;
        group_ = next_group_;
        if (group_ & 8) {
            ++instruction_count_;
            trap_ = (flags() & 0x100) != 0;
            boundary_checked_ = false;
        }
    }

    void startInterrupt() {
        segment_override_.reset();
        f1_ = repne_ = lock_ = read_prefix_ = false;
        configure_instruction(0, 0, interruptGroup, true);
        microcode_pointer_ = interrupt_entry_;
        interrupt_entry_ = 0;
        rni_ = nx_ = false;
        in_instruction_ = true;
        state_ = stateRunning;
        trap_ = false;
        pending_ = invalidMethod;
        eu_ = Running;
        loader_ = 2;
    }

    void startMicrocode(uint8_t modrm) {
        loader_ = 2;
        startInstruction();
        read_prefix_ = false;
        const auto& instruction = mc_instruction_table[opcode_];
        configure_instruction(opcode_, modrm, group_, instruction.word);
        // Loading SS suppresses interrupts through the following instruction.
        if (opcode_ == 0x17 || (opcode_ == 0x8e && modRMReg() == 2)) {
            all_shadow_ = true;
        }
        microcode_pointer_ = instruction.entry[modRMReg()];
        state_ = instruction.extensionDelay ? stateSingleCycleWait : stateRunning;
        rni_ = false;
        in_instruction_ = true;

        if (use_memory_) {
            const auto& ea = mc_ea_table[modrm];
            segment_ = ea.segment;
            microcode_return_ = microcode_pointer_;
            microcode_pointer_ = ea.startAddress;
            state_ = stateSingleCycleWait;
        }

        pending_ = invalidMethod;
        eu_ = Running;
    }

    void startDiscrete() {
        loader_ = 0;
        startInstruction();
        read_prefix_ = false;

        if (group_ & 0x400000) {
            locking_ = true;
            read_prefix_ = true;

            return;
        }

        if (group_ & 0x100000) {
            f1_ = true;
            repne_ = !(opcode_ & 1);
            read_prefix_ = true;

            return;
        }

        if (group_ & 0x200000) {
            segment_override_ = Segment((opcode_ >> 3) & 3);
            read_prefix_ = true;

            return;
        }

        if (opcode_ == 0xf4) {
            loader_ = 2;
            rni_ = nx_ = false;
            eu_ = HaltingStart;
            extra_halt_delay_ =
                !((bus_ == TState::TIdle && !t5_ && !t6_ && bus_status_ == BusStatus::Passive) ||
                  (t5_ && last_bus_status_ != BusStatus::InstructionFetch));
        }
        else if (opcode_ == 0xf5) {
            // CMC
            flags() ^= 1;
        }
        else if ((opcode_ & 0xfe) == 0xf8) {
            // CLC and STC
            flags() = (flags() & ~1) | (opcode_ & 1);
        }
        else if ((opcode_ & 0xfe) == 0xfa) {
            // CLI and STI
            flags() = (flags() & ~0x200) | ((opcode_ & 1) << 9);
            if (opcode_ == 0xfb) {
                intr_shadow_ = true;
            }
        }
        else if ((opcode_ & 0xfe) == 0xfc) {
            // CLD and STD
            flags() = (flags() & ~0x400) | ((opcode_ & 1) << 10);
        }
        else {
            assert(false && "unhandled clocked discrete instruction");
        }
    }

    void startBus() {
        bool memory = group_ & groupMemory;

        if (request_.acknowledge) {
            bus_status_ = BusStatus::InterruptAcknowledge;
        }
        else if (request_.write) {
            bus_status_ = memory ? BusStatus::MemoryWrite : BusStatus::IoWrite;
        }
        else {
            bus_status_ = memory ? BusStatus::MemoryRead : BusStatus::IoRead;
        }
    }

    uint32_t busAddress(uint16_t offset) { return io_segment_ == 9 ? offset : physical(io_segment_, offset); }

    void accessDone(uint8_t high) {
        opr() |= uint16_t(high) << 8;

        if (request_.complete) {
            rni_ = true;
            in_instruction_ = false;
        }

        switch (request_.indexUpdate) {
            case 0:
                ind() += 2;
                break;

            case 1:
                ind() += (word_size_ ? 2 : 1) * (df() ? -1 : 1);
                break;

            case 2:
                ind() -= 2;
                break;
        }

        eu_ = Running;
    }

    template <bool Capture>
    MARTY_CPU_FORCE_INLINE void executeEU(Cycle* snapshot) {
        switch (eu_) {
            case Suspend:
                if (bus_ == TState::T4) {
                    eu_ = Running;
                }

                return;

            case CorrectPC:
                if (bus_status_ == BusStatus::Passive && bus_ != TState::T4 && !t4_) {
                    pc() -= uint16_t(queue_bytes_);
                    queue_bytes_ = 0;
                    eu_ = Running;
                }

                return;

            case IODelay2:
                if (!ready_ && (bus_ == TState::T3 || bus_ == TState::TWait)) {
                    return;
                }
                eu_ = IODelay1;

                return;

            case IODelay1:
                if (bus_ != TState::T4) {
                    eu_ = FirstStart;
                }

                return;

            case FirstStart:
                if (bus_status_ != BusStatus::Passive) {
                    return;
                }

                io_write_ = is8086() ? opr() : uint8_t(opr());
                io_segment_ = request_.segment;

                if (io_segment_ == 3) {
                    io_segment_ =
                        int(segment_override_.value_or((group_ & groupEffectiveAddress) ? segment_ : Segment::DS));
                }
                else if (io_segment_ == 1) {
                    io_segment_ = 9;
                }

                io_index_ = ind();
                io_address_ = busAddress(io_index_);
                bus_word_ = is8086() && word_size_ && !(io_address_ & 1);
                eu_ = FirstDone;
                startBus();

                return;

            case FirstDone:
                if (!word_size_ || bus_word_) {
                    io_requested_ = false;
                }

                if (bus_status_ != BusStatus::Passive) {
                    return;
                }

                io_write_ = is8086() ? uint16_t((opr() >> 8) | (opr() << 8)) : uint8_t(opr() >> 8);
                opr() = io_read_;

                if (!word_size_ || bus_word_) {
                    accessDone(0);
                }
                else {
                    opr() &= 0xff;
                    io_index_ = uint16_t(ind() + 1);
                    io_address_ = busAddress(io_index_);
                    eu_ = SecondDone;
                    startBus();
                }

                return;

            case SecondDone:
                io_requested_ = false;

                if (bus_status_ == BusStatus::Passive) {
                    accessDone(io_read_);
                }

                return;

            case HaltingStart:
                prefetching_ = false;
                eu_ = bus_status_ == BusStatus::Passive ? Halting2 : Halting3;
                return;
            case Halting3:
                if (bus_status_ == BusStatus::Passive) {
                    eu_ = Halting2;
                }
                return;
            case Halting2:
                if constexpr (Capture) {
                    snapshot->loggerStatus = static_cast<int8_t>(BusStatus::Halt);
                }
                eu_ = Halting1;
                return;
            case Halting1:
                eu_ = Halted;
                return;
            case Halted:
                if constexpr (Capture) {
                    snapshot->loggerStatus = static_cast<int8_t>(BusStatus::Passive);
                }
                if (!nmi_pending_ && !(intr_line_ && (flags() & 0x200))) {
                    return;
                }
                if (extra_halt_delay_) {
                    extra_halt_delay_ = false;
                    return;
                }
                rni_ = true;
                in_instruction_ = false;
                eu_ = Running;
                return;
            case Running:
                break;
        }

        if (state_ == stateSingleCycleWait) {
            state_ = stateRunning;

            return;
        }

        if (state_ == stateWaitingForQueueData && !queue_bytes_) {
            return;
        }

        if (pending_ == invalidMethod) {
            assert(microcode_pointer_ < 8192 && "invalid generated entry address");

            if constexpr (Capture) {
                snapshot->microcodePointer = static_cast<int16_t>(microcode_pointer_);
            }
            const auto entry = resolveDispatch(microcode_pointer_, microcode_methods_);

            assert(entry.method != invalidMethod && "unmapped generated entry");

            pending_ = entry.method;
            microcode_pointer_ = entry.next;
        }

        state_ = stateRunning;
#include "microcode_dispatch.inc"


        if (state_ != stateWaitingForQueueData) {
            pending_ = invalidMethod;
        }
    }

public:
    template <class Host>
    void clock(Host& host) {
        clockImpl<false>(host, nullptr);
    }

    // SST and explicit trace callers supply storage; ordinary clocks have none.
    template <class Host>
    void clockWithCycles(Host& host, Cycle& snapshot) {
        snapshot = {};
        clockImpl<true>(host, &snapshot);
    }

private:
    template <bool Capture, class Host>
    void clockImpl(Host& host, Cycle* snapshot) {
        next_instruction_ = false;
        ready_ = host.ready();
        interrupt_pending_ = nmi_pending_ || (intr_line_ && (flags() & 0x200) && !intr_shadow_ && !all_shadow_);
        TState nextBus = bus_;
        bool writing = bus_status_ == BusStatus::MemoryWrite || bus_status_ == BusStatus::IoWrite;
        bool prefetchComplete = false;
        const bool completingWord = last_bus_word_;

        // Queue activity during clock N drives QS0/QS1 in clock N+1. Latch
        // before executing this clock's EU/loader, and default the next clock
        // to 00 so a stall or prefetch alone cannot repeat a dequeue pulse.
        const uint8_t queueStatus = static_cast<uint8_t>(next_queue_status_);
        qs0_pin_ = (queueStatus & 1) != 0;
        qs1_pin_ = (queueStatus & 2) != 0;
        queue_byte_pin_ = next_queue_byte_;
        if constexpr (Capture) {
            snapshot->qs0 = qs0_pin_;
            snapshot->qs1 = qs1_pin_;
            snapshot->queueByte = queue_byte_pin_;
            snapshot->t = bus_;
            snapshot->ready = ready_;
        }
        next_queue_status_ = QueueReadState::NoOperation;
        next_queue_byte_ = 0;
        t6_ = t5_;
        t5_ = t4_;
        t4_ = false;
        const auto cycleBusStatus = bus_status_;

        switch (bus_) {
            case TState::T1:
                host.startAccess(io_address_, bus_status_, bus_word_ ? 2 : 1);
                address_bus_ = io_address_;
                bhe_pin_ = is8086() && !bus_word_ && !(io_address_ & 1);
                if constexpr (Capture) {
                    snapshot->ale = true;
                }
                nextBus = TState::T2;
                break;

            case TState::T2:
                {
                    unsigned seg = io_segment_ == 0 ? 0 : io_segment_ == 2 ? 1 : io_segment_ == 3 ? 3 : 2;
                    address_bus_ = (address_bus_ & 0x0ffff) | (seg << 16) | (flags() & 0x200 ? 0x40000 : 0);

                    if (writing) {
                        const uint16_t pins =
                            is8086() && (io_address_ & 1) ? uint16_t((io_write_ << 8) | (io_write_ >> 8)) : io_write_;
                        address_bus_ = (address_bus_ & (is8086() ? 0xf0000 : 0xfff00)) | pins;
                    }

                    if (bus_status_ == BusStatus::InterruptAcknowledge) {
                        host.setLock(eu_ == FirstDone);
                    }
                    nextBus = TState::T3;
                    break;
                }

            case TState::T3:
            case TState::TWait:
                if (bus_status_ == BusStatus::InstructionFetch &&
                    queue_bytes_ - unsigned(dequeueing_) + (bus_word_ ? 2 : 1) >= (is8086() ? 5u : 4u)) {
                    queue_filled_ = true;
                }
                if (!ready_) {
                    nextBus = TState::TWait;
                    break;
                }
                last_bus_word_ = bus_word_;
                if (writing) {
                    io_read_ = io_write_;
                    committed_write_ = io_write_;
                }
                else {
                    io_read_ = host.read();
                }
                host.setPassiveOrHalt(true);

                if (is8086()) {
                    if (bus_word_) {
                        if constexpr (Capture) {
                            snapshot->data = io_read_;
                        }
                        address_bus_ = (address_bus_ & 0xf0000) | io_read_;
                    }
                    else if (io_address_ & 1) {
                        const auto data = uint16_t(io_read_ << 8);
                        if constexpr (Capture) {
                            snapshot->data = data;
                        }
                        address_bus_ = (address_bus_ & 0xf00ff) | data;
                    }
                    else {
                        const auto data = io_read_ & 0xff;
                        if constexpr (Capture) {
                            snapshot->data = data;
                        }
                        address_bus_ = (address_bus_ & 0xfff00) | data;
                    }

                    // A byte read also latches the undriven lane. On odd accesses
                    // the BIU exchanges the two lanes before delivering OPR.
                    io_read_ = uint16_t(address_bus_);

                    if (io_address_ & 1) {
                        io_read_ = uint16_t((io_read_ << 8) | (io_read_ >> 8));
                    }
                }
                else {
                    if constexpr (Capture) {
                        snapshot->data = io_read_;
                    }
                    address_bus_ = (address_bus_ & 0xfff00) | io_read_;
                }

                last_bus_status_ = bus_status_;
                bus_status_ = BusStatus::Passive;
                nextBus = TState::T4;
                break;

            case TState::T4:
                if (last_bus_status_ == BusStatus::MemoryWrite || last_bus_status_ == BusStatus::IoWrite) {
                    host.write(committed_write_);
                }
                if (last_bus_status_ == BusStatus::InstructionFetch) {
                    prefetchComplete = true;
                }

                nextBus = TState::TIdle;
                t4_ = true;
                break;

            case TState::TIdle:
                if (aborted_prefetch_ && eu_ == IODelay1) {
                    bhe_pin_ = !word_size_;
                    aborted_prefetch_ = false;
                }

                break;
        }

        if constexpr (Capture) {
            snapshot->address = address_bus_;
            snapshot->bhe = bhe_pin_;
            snapshot->status =
                static_cast<uint8_t>((bus_ == TState::T1 || bus_ == TState::T2 ||
                                      ((bus_ == TState::T3 || bus_ == TState::TWait) && !ready_))
                                         ? cycleBusStatus
                                         : BusStatus::Passive);
            if (eu_ == Halting1) {
                snapshot->status = static_cast<uint8_t>(BusStatus::Halt);
            }

            if (bus_ == TState::T2 || bus_ == TState::T3 || bus_ == TState::TWait ||
                bus_ == TState::T4) {
                snapshot->segment = (address_bus_ >> 16) & 3;

                if (bus_ != TState::T4) {
                    if (cycleBusStatus == BusStatus::InstructionFetch ||
                        cycleBusStatus == BusStatus::MemoryRead) {
                        snapshot->memory = 4;
                    }

                    if (cycleBusStatus == BusStatus::MemoryWrite) {
                        snapshot->memory = bus_ == TState::T2 ? 2 : 3;
                    }

                    if (cycleBusStatus == BusStatus::IoRead) {
                        snapshot->io = 4;
                    }

                    if (cycleBusStatus == BusStatus::IoWrite) {
                        snapshot->io = bus_ == TState::T2 ? 2 : 3;
                    }
                }
            }
            else {
                snapshot->segment = 4;
            }
        }

        if (dequeueing_) {
            dequeueing_ = false;
            --queue_bytes_;
        }

        if ((queue_bytes_ < 3 ||
             (bus_ == TState::TIdle &&
              (last_bus_status_ != BusStatus::InstructionFetch || (!t4_ && !t5_)))) &&
            bus_ == TState::TIdle && !(t4_ && last_bus_status_ == BusStatus::InstructionFetch) &&
            queue_bytes_ < (is8086() ? 5u : 4u)) {
            queue_filled_ = false;
        }

        if (loader_ & 2) {
            executeEU<Capture>(snapshot);
        }

        if (locking_) {
            locking_ = false;
            lock_ = true;
            host.setLock(true);
        }

        const bool previousLock = lock_;
        switch (loader_) {
            case 0:
                readOpcode(0);
                break;

            case 1:
            case 3:
                if (interrupt_entry_) {
                    startInterrupt();
                }
                else if (!(next_group_ & 0x400)) {
                    startDiscrete();
                }
                else if (!(next_group_ & groupEffectiveAddress)) {
                    startMicrocode(0);
                }
                else {
                    loader_ = 1;

                    if (queue_bytes_) {
                        startMicrocode(queueRead(QueueReadState::SubsequentByte));
                    }
                }

                break;

            case 2:
                if (rni_) {
                    readOpcode(0);
                }
                else if (nx_) {
                    readOpcode(2);
                }

                break;
        }

        if (previousLock && !lock_) {
            host.setLock(false);
        }

        if (prefetchComplete) {
            queue.push_back(uint8_t(io_read_), pc());
            ++queue_bytes_;
            ++pc();

            if (completingWord) {
                queue.push_back(uint8_t(io_read_ >> 8), pc());
                ++queue_bytes_;
                ++pc();
            }
        }

        if (nextBus == TState::TIdle && bus_status_ != BusStatus::Passive) {
            nextBus = TState::T1;
            host.setPassiveOrHalt(bus_status_ == BusStatus::Halt);

            if (bus_status_ == BusStatus::InstructionFetch) {
                io_index_ = pc();
                io_address_ = physical(1, pc());
                bus_word_ = is8086() && !(io_address_ & 1);
            }
        }

        if (canPrefetch()) {
            bus_status_ = BusStatus::InstructionFetch;
            io_segment_ = 1;
        }

        if (flushing_) {
            flushing_ = false;
            prefetching_ = true;
        }

        if constexpr (Capture) {
            snapshot->lock = lock_;
            snapshot->nextBus = nextBus;
            snapshot->nextIoType = static_cast<uint8_t>(bus_status_);
            snapshot->interruptFlag = (flags() & 0x200) != 0;
        }

        bus_ = nextBus;
        ++cycle_count_;
        intr_line_ = host.interruptPending();
        host.tick();
        if (next_instruction_) {
            checkExecutionBreakpoint(next_cs_, next_ip_);
        }
    }
};

} // namespace marty::intel

#undef MARTY_CPU_FORCE_INLINE
