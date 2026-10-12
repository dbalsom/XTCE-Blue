// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Andrew Jenner
// Copyright (C) 2026 Daniel Balsom
#ifndef CPU_H
#define CPU_H

#include <SDL3/SDL_log.h>
#include <cassert>
#include <deque>
#include <format>
#include <iomanip>
#include <iostream>
#include <span>
#include <string>
#include <sstream>
#include <utility>

#include "../../xtce_blue.h"
#include "../Bus.h"
#include "../Logger.h"
#include "../CycleLogMicrocode.h"

#include "../cpu_types.h"
#include "../PrefetchQueue.h"
#include "../execution_control.h"
#include "microcode.h"

#define LINE_ENDING_SIZE 1
#define DEBUG_MC 0

template <typename BusType = Bus, typename WordT = uint8_t, std::size_t QueueLen = 4>
class Cpu : public cpu::ExecutionControl
{

    static_assert(std::is_same_v<WordT, uint8_t> || std::is_same_v<WordT, uint16_t>,
                  "Cpu WordT must be uint8_t or uint16_t");
    static_assert(QueueLen > 0, "QueueLen must be > 0");

    enum GroupDecodeFlags
    {
        // The original 15 outputs of the Group decode PLA
        groupMemory = 1, // This signal controls the M/IO (S2) status line
        groupInitialEARead = 2, // This signal indicates that the effective address is read by the instruction.
        groupMicrocodePointerFromOpcode = 4, // Group 3/4/5 opcode - microcode address will be determined by ModR/M.
        groupNonPrefix = 8, // This line controls whether the instruction is a prefix or not.
        groupEffectiveAddress = 0x10, // This signal indicates whether the instruction has a ModR/M byte.
        groupAddSubBooleanRotate = 0x20, // This signal specifies the top bit for an ALU operation.
        groupNonFlagSet = 0x40, // This signal determines whether the instruction directly updates flags (not CMC).
        groupMNotAccumulator = 0x80, // This signal controls whether the instruction uses the AL or AX register for M.
        groupNonSegregEA = 0x100, // This signal controls whether an instruction indexes a segment register.
        groupNoDirectionBit = 0x200, // This signal controls whether an opcode encodes a direction bit.
        groupMicrocoded = 0x400, // This signal indicates whether the instruction is microcoded or not.
        groupNoWidthInOpcodeBit0 = 0x800, // This signal indicates whether the opcode encodes width in bit 0
        groupByteOrWordAccess = 0x1000, // This signal indicates whether the instruction accesses byte or word data.
        groupF1ZZFromPrefix = 0x2000,
        groupIncDec = 0x4000, // This signal indicates whether carry is allowed to be updated.

        // Direct column outputs
        groupLoadRegisterImmediate = 0x10000,
        groupWidthInOpcodeBit3 = 0x20000,
        groupCMC = 0x40000,
        groupHLT = 0x80000,
        groupREP = 0x100000,
        groupSegmentOverride = 0x200000,
        groupLOCK = 0x400000,
        groupCLI = 0x800000,

        // This is not part of the PLA outputs, but we derive it here for convenience
        groupLoadSegmentRegister = 0x1000000,
    };

public:
    enum MicrocodeState
    {
        stateRunning,
        stateWaitingForQueueData,
        stateWaitingForQueueIdle,
        stateIODelay2,
        stateIODelay1,
        stateWaitingUntilFirstByteCanStart,
        stateWaitingUntilFirstByteDone,
        stateWaitingUntilSecondByteDone,
        stateSingleCycleWait,
        stateHaltingStart,
        stateHalting3,
        stateHalting2,
        stateHalting1,
        stateHalted,
        stateSuspending,
    };

    using QueueEntry = cpu::PrefetchEntry;

    struct InstructionHistoryEntry
    {
        uint16_t cs{};
        uint16_t ip{};
        std::string disassembly;
    };

    // Default constructor: default-construct the bus and initialize CPU state
    Cpu() : console_logging_(false), bus_() { initializeCommon(); }

    // Forwarding constructor: allow callers to construct CpuT with arguments forwarded to BusType's constructor.
    template <typename... Args>
    explicit Cpu(Args&&... args) : console_logging_(false), bus_(std::forward<Args>(args)...) {
        initializeCommon();
    }

    MicrocodeState getMCState() const { return state_; }
    BusType* getBus() { return &bus_; }
    [[nodiscard]] uint8_t getALU() const { return alu_; }
    uint8_t* getRAM() { return bus_.ram(); }
    uint16_t* getMainRegisters() { return &registers_[24]; }
    uint16_t* getRegisters() { return &registers_[0]; }
    void stubInit() { bus_.stubInit(); }

    void setExtents(const int logStartCycle, const int logEndCycle, const int executeEndCycle, const int stopIP,
                    const int stopSeg) {
        log_start_cycle_ = logStartCycle + 4;
        log_end_cycle_ = logEndCycle;
        execute_end_cycle_ = executeEndCycle;
        stop_ip_ = stopIP;
        stop_seg_ = stopSeg;
    }

    void setLogInstructions(const bool state) { log_instructions_ = state; }

    [[nodiscard]] bool isLogInstructions() const { return log_instructions_; }

    std::vector<InstructionHistoryEntry> getHistory(size_t lines) { return history_.getLast(lines); }

    [[nodiscard]] uint16_t getInstructionPointer() const { return inst_address_; }

    void setInitialIP(const int v) { pc() = v; }
    [[nodiscard]] uint64_t cycle() const { return cycle_ >= 11 ? cycle_ - 11 : 0; }
    [[nodiscard]] uint64_t instructionCount() const { return instruction_count_; }
    [[nodiscard]] QueueReadState getQueueStatus() const { return queue_status_; }

    void setBusCycleCapture(bool enabled) { capture_bus_cycles_ = enabled; }
    [[nodiscard]] const CpuBusCycle& getBusCycle() const { return bus_cycle_; }

    // Call after reset and setting CS:IP, before execution. PC is the BIU's
    // fetch pointer, so advance it past the bytes already present in the queue.
    void setPrefetchQueue(std::span<const uint8_t> bytes) {
        static_assert(sizeof(WordT) == 1, "Byte queue initialization is for the 8088");
        assert(bytes.size() <= QueueLen && "Initial prefetch queue exceeds CPU capacity");
        queue_bytes_ = 0;
        prefetch_queue_.clear();
        dequeueing_ = false;
        for (const auto byte : bytes) {
            prefetch_queue_.push_word(byte, pc());
            ++queue_bytes_;
            ++pc();
        }
        queue_filled_ = bytes.size() == QueueLen;
    }

    [[nodiscard]] std::string log() const {
        // Assemble buffered lines into a single string on request
        std::string out;
        std::string line;
        for (const auto& entry : log_buffer_) {
            formatCycleLogEntry(entry, line);
            out += line;
        }
        return out;
    }

    void reset() {
        //bus_.reset();
        for (unsigned short& register_value : registers_) {
            register_value = 0;
        }
        setBytePointers();
        inst_boundary_ = false;
        registers_[1] = 0xFFFF; // RC (CS)
        registers_[21] = 0xFFFF; // ONES
        registers_[15] = 2; // FLAGS

        cycle_ = 0;
        microcode_pointer_ = 0x1800;
        bus_state_ = TState::TIdle;
        bus_status_ = BusStatus::Passive;
        logger_.reset();
        prefetching_ = true;
        clearCycleLog();
        pc() = 0;
        nmi_requested_ = false;
        alu_ = 0;
        alu_input_ = 0;
        queue_bytes_ = 0;
        queue_filled_ = false;
        prefetch_queue_ = {};
        segment_override_ = -1;
        f1_ = false;
        repne_ = false;
        lock_ = false;
        loader_state_ = 0;
        read_prefix_ = false;
        last_microcode_pointer_ = -1;
        dequeueing_ = false;
        io_cancelling_ = 0;
        io_requested_ = false;
        t4_ = false;
        prefetch_delayed_ = false;
        queue_flushing_ = false;
        last_bus_status_ = BusStatus::Passive;
        t5_ = false;
        t6_ = false;
        interrupt_pending_ = false;
        ready_ = true;
        //cycles_until_can_lower_queue_filled_ = 0;
        locking_ = false;
        breakpoint_hit_ = false;

        // Reset flags
        carry_ = false;
        carry_latch_ = false;
        zero_ = false;
        super_zero_ = false;
        auxiliary_ = false;
        sign_ = false;
        parity_ = false;
        overflow_ = false;

        // Instruction tracking
        rni_ = false;
        nx_ = false;
        in_instruction_ = false;
        state_ = stateRunning;
        queue_status_ = QueueReadState::NoOperation;
        next_queue_status_ = QueueReadState::NoOperation;
        next_queue_byte_ = 0;
        bus_cycle_ = {};
        bus_segment_status_ = 4;
        inst_address_ = 0;
        instruction_count_ = 0;
        history_.clear();

        resetExecutionControl();
    }

    RunResult run_for(const int cycleCt) {

        inst_boundary_ = false;
        sanity_check();
        beginRun();

        for (int i = 0; i < cycleCt; i++) {
            simulateCycle();

            // If we've reached an instruction boundary this cycle, check the breakpoint
            if (inst_boundary_) {
                inst_boundary_ = false;
                checkExecutionBreakpoint(cs(), getRealIP());
            }

            if (breakpoint_hit_) {
                // Stop executing further cycles if a breakpoint was hit by other means
                return RunResult::BreakpointHit;
            }

            if (off_rails_) {
                return RunResult::OffRails;
            }
        }

        return RunResult::Ok;
    }

    void run() {
        do {
            simulateCycle();
        }
        while ((getRealIP() != stop_ip_ + 2 || cs() != stop_seg_) && cycle_ < execute_end_cycle_);
    }

    void setConsoleLogging() { console_logging_ = true; }

    // Run CPU cycles until the next instruction boundary is reached.
    // Returns the number of CPU cycles executed.
    int stepToNextInstruction() {
        inst_boundary_ = false;
        int cycles = 0;
        // if rni_ is true, clear it first by cycling the CPU until it becomes false.
        while (rni_ && state_ != stateHalted) {
            simulateCycle();
        }
        //rni_ = false;
        // Run cycles until rni_ becomes true or the CPU halts.
        while (!inst_boundary_ && state_ != stateHalted) {
            simulateCycle();
            ++cycles;
            // Prevent infinite loop in funky situations by limiting cycles
            if (cycles > 1000000) {
                break;
            }
        }
        return cycles;
    }

    void setRegister(const Register r, const uint16_t v) { registers_[reg_to_idx(r)] = v; }

    uint16_t getRegister(const Register r) const { return registers_[reg_to_idx(r)]; }

    uint16_t getRealIP() { return pc() - queue_bytes_; }

    void setTestNumber(uint32_t n) { test_number_ = n; }

private:
    void setBytePointers() {
        // Initialize byte_registers_ as byte pointers into registers_.
        // Endianness is checked by setting a known value and examining the first byte.
        // This is clever, but it makes Cpu not object-safe for assignment/relocation.
        registers_[24] = 0x100;
        const auto byteData = reinterpret_cast<uint8_t*>(&registers_[24]);
        const int bigEndian = *byteData;
        for (int i = 0; i < 8; ++i) {
            const int byteNumbers[8] = {0, 2, 4, 6, 1, 3, 5, 7};
            // The index will be XOR'd with either 0 (little-endian) or 1 (big-endian) to flip the byte order
            // if required.
            byte_registers_[i] = &byteData[byteNumbers[i] ^ bigEndian];
        }
    }

    // Extracted common initialization logic so we can reuse it in all constructors.
    void initializeCommon() {
        log_start_cycle_ = 0;
        log_end_cycle_ = UINT64_MAX;

        setBytePointers();

        registers_[21] = 0xffff;
        registers_[23] = 0;

        // std::cout << "CPU initializing." << std::endl;

        // Initialize the microcode data and put it in a format more suitable for interpreting

        // Select 8086 based on template WordT parameter.
        static constexpr bool use8086 = std::is_same_v<WordT, uint16_t>;
        const std::string_view microcodeRomLeft = use8086 ? MICROCODE_ROM_LEFT_8086 : MICROCODE_ROM_LEFT_8088;
        const std::string_view microcodeRomRight = use8086 ? MICROCODE_ROM_RIGHT_8086 : MICROCODE_ROM_RIGHT_8088;

        // Initialize an array to hold the 512 21-bit microcode instruction words.
        uint32_t instructions[512];
        for (unsigned int& instruction : instructions) {
            instruction = 0;
        }

        // Load the main microcode ROM
        // Iterate through 84 rows of microcode data.
        for (int y = 0; y < 84; ++y) {
            // Iterate through left and right columns.
            for (int half = 0; half < 2; ++half) {
                const std::string_view s = half == 1 ? microcodeRomLeft : microcodeRomRight;
                // Iterate through the width of the ROM block (64).
                for (int x = 0; x < 64; ++x) {
                    int b = s[y * (64 + LINE_ENDING_SIZE) + (63 - x)] == '0' ? 1 : 0;
                    instructions[x * 8 + half * 4 + y % 4] |= (b << (20 - (y >> 2)));
                }
            }
        }

        for (int i = 0; i < 512; ++i) {
            int w = instructions[i];
#if DEBUG_MC
            std::cout << std::format("{:03X}: {:021b}\n", i, static_cast<unsigned int>(w));
#endif

            // The microcode word is somewhat scrambled compared to the word layout diagram you may have seen in online
            // documentation. We unscramble it here and store the decoded fields in the microcode_ array.

            // See https://www.righto.com/2022/11/how-8086-processors-microcode-engine.html for an in-depth description
            // of the microcode format.

            // Decode Type. There are 6 different types of micro-instruction, implying a different word format.
            // All word formats share a source field, destination field, and 'update flags' flag, so we can decode the
            // common fields here.

            // The type field is either 2 or 3 bits. If 3 bits, the high bit is set.
            int typ = (w >> 7) & 7;
            if ((typ & 4) == 0) {
                // High bit is not set, so this is a 2-bit type field. Shift right to discard the low bit.
                typ >>= 1;
            }

            // Decode Source field
            int s = ((w >> 13) & 1) + ((w >> 10) & 6) + ((w >> 11) & 0x18);

            // Decode Destination field
            int d = ((w >> 20) & 1) + ((w >> 18) & 2) + ((w >> 16) & 4) + ((w >> 14) & 8) + ((w >> 12) & 0x10);

            // Decode 'update flags' flag
            int f = (w >> 10) & 1;

            // microcode_ has four bytes for each decoded word - Destination, Source, (F + type), Operands
            microcode_[i * 4] = d;
            microcode_[i * 4 + 1] = s;
            microcode_[i * 4 + 2] = (f << 3) + typ; // Pack F and type together
            microcode_[i * 4 + 3] = w & 0xff; // Low 8 bits are operands - they require further unpacking.
        }

#if DEBUG_MC
        std::cout << "Instruction words loaded." << std::endl;
#endif

        // Read in the stage1 decoder PLA ROM logic.
        // The 8088 utilizes a "match decoder" which takes an 11-bit input and activates one column of the microcode
        // ROM. This decoder is implemented as a programmable logic array (PLA) with 128 columns. The match logic
        // allows a match on 0, 1, or "don't care" for each of the 11 input bits.

        // To implement efficient microcode lookups, we expand the PLA data into a full 11-bit (2048-entry) lookup
        // table, microcode_index_. This LUT is by nature sparse, but we shouldn't ever attempt to access a non-mapped
        // entry during normal operation.
        int stage1[128]{};

        // The top and bottom decoder images combine the former nine horizontal fragments into full-width rows.
        for (int h = 0; h < 2; ++h) {
            constexpr int decoderHeight = 11;
#if DEBUG_MC
            std::cout << "Loading " << (h == 0 ? "top" : "bottom") << " microcode decoder" << std::endl;
#endif
            const std::string_view decoder = h == 0 ? MICROCODE_DECODER_TOP : MICROCODE_DECODER_BOTTOM;

            for (int y = 0; y < decoderHeight; ++y) {
                constexpr int decoderWidth = 128;
                for (int x = 0; x < decoderWidth; ++x) {
                    const bool programmed = decoder[y * (decoderWidth + LINE_ENDING_SIZE) + x] == '0';
                    if (programmed) {
                        // Stage1 is written in reverse-order.
                        stage1[decoderWidth - 1 - x] |= 1 << (y * 2 + (h ^ (y <= 2 ? 1 : 0)));
                    }
                }
            }
        }

        // Iterate through all possible 11-bit input combinations (2048), simulating all possible inputs into the
        // decoder PLA.
        for (int i = 0; i < 2048; ++i) {
            static const int ba[] = {7, 2, 1, 0, 5, 6, 8, 9, 10, 3, 4};

            // Scan through the decoder. There is one decoder column for every 4 microcode words.
            for (int j = 0; j < 128; ++j) {
                int s1 = stage1[j];
                // Skip empty decoder slots as they cannot match anything
                if (s1 == 0) {
                    continue;
                }
                bool matches = true;
                // The decoder uses 11-bit matches. Increment a bit index from 0..10.
                for (int b = 0; b < 11; ++b) {
                    int x = (s1 >> (ba[b] * 2)) & 3;
                    int ib = (i >> (10 - b)) & 1;
                    if (!(x == 0 || (x == 1 && ib == 1) || (x == 2 && ib == 0))) {
                        matches = false;
                        break;
                    }
                }

                if (matches) {
                    // This 11-bit input matches this decoder column, save it to the LUT.
                    microcode_index_[i] = j;
                    break;
                }
            }
        }

        // Decode the translation PLA.
        // The translation PLA takes 8 bits of input and outputs a full 13-bit microcode address and a 1-bit segment
        // specifier.

        // The inputs vary depending on the type of lookup.
        // For looking up an EA calculation microcode address, the inputs are 5 bits from the ModRM byte.

#if DEBUG_MC
        std::cout << "Loading " << (use8086 ? "8086" : "8088") << " translation ROM" << std::endl;
#endif
        const std::string_view translationString = use8086 ? MICROCODE_TRANSLATION_8086 : MICROCODE_TRANSLATION_8088;
        int tsp = 0;
        char c = translationString[0];

        // Iterate through the first 33 rows of the translation file (empty lines will be skipped)
        for (int i = 0; i < 33; ++i) {
            int mask = 0;
            int bits = 0;
            int output = 0;

            // Iterate through the 8-character match mask that starts each line, constructing a bit mask
            // for matching.
            for (int j = 0; j < 8; ++j) {
                if (c != '?') {
                    mask |= 128 >> j;
                }
                if (c == '1') {
                    bits |= 128 >> j;
                }
                c = translationString[++tsp];
            }

            // Iterate through the 14-character addresses corresponding to each match mask
            for (int j = 0; j < 14; ++j) {
                while (c != '0' && c != '1') {
                    // Skip any whitespace
                    c = translationString[++tsp];
                }
                if (c == '1') {
                    // Set the corresponding output bit
                    output |= 8192 >> j;
                }
                c = translationString[++tsp];
            }
            // Consume rest of line
            while (c != 0x0A) {
                c = translationString[++tsp];
            }
            // Consume newlines
            while (c == 0x0A) {
                c = translationString[++tsp];
            }

            for (int j = 0; j < 256; ++j) {
                if ((j & mask) == bits) {
#if DEBUG_MC
                    std::cout << "Translation output: " << std::format("{:02X}: {:014b}\n", j, output);
#endif
                    translation_[j] = output;
                }
            }
        }

        // Decode the group decode PLA.
        // The group decode PLA takes 9 bits of input (from opcode and prefixes) and outputs 15 control bits.

        // For a detailed examination of the group decode PLA, see
        // https://www.righto.com/2023/05/8086-processor-group-decode-rom.html

        int groupInput[38 * 18];
        int groupOutput[38 * 15];
        constexpr std::string_view groupString = MICROCODE_GROUP_DECODER;

        // Iterate through each column of the group decode ROM.
        for (int x = 0; x < 38; ++x) {
            // Iterate through the first 15 rows of the group decode ROM.
            for (int y = 0; y < 15; ++y) {
                groupOutput[y * 38 + x] = groupString[y * (38 + LINE_ENDING_SIZE) + x] == '0' ? 0 : 1;
            }
            for (int y = 0; y < 18; ++y) {
                c = groupString[((y / 2) + 15) * (38 + LINE_ENDING_SIZE) + x];
                if ((y & 1) == 0) {
                    groupInput[y * 38 + x] = (c == '*' || c == '0') ? 1 : 0;
                }
                else {
                    groupInput[y * 38 + x] = (c == '*' || c == '1') ? 1 : 0;
                }
            }
        }
        static const int groupYY[18] = {1, 0, 3, 2, 4, 6, 5, 7, 11, 10, 12, 13, 8, 9, 15, 14, 16, 17};
        for (int x = 0; x < 34; ++x) {
            if (x == 11) {
                // Column 11 doesn't activate any outputs.
                continue;
            }

            for (int i = 0; i < 0x101; ++i) {
                bool found = true;
                for (int j = 0; j < 9; ++j) {
                    int y0 = groupInput[groupYY[j * 2] * 38 + x];
                    int y1 = groupInput[groupYY[j * 2 + 1] * 38 + x];
                    int b = (i >> j) & 1;
                    if ((y0 == 1 && b == 1) || (y1 == 1 && b == 0)) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    int g = 0;
                    for (int j = 0; j < 15; ++j) {
                        g |= groupOutput[j * 38 + x] << j;
                    }
                    if (x == 10) {
                        g |= groupLoadRegisterImmediate;
                    }
                    if (x == 12) {
                        g |= groupWidthInOpcodeBit3;
                    }
                    if (x == 13) {
                        g |= groupCMC;
                    }
                    if (x == 14) {
                        g |= groupHLT;
                    }
                    if (x == 31) {
                        g |= groupREP;
                    }
                    if (x == 32) {
                        g |= groupSegmentOverride;
                    }
                    if (x == 33) {
                        g |= groupLOCK;
                    }
                    if (i == 0xFA) {
                        g |= groupCLI;
                    }
                    if (i == 0x8E || (i & 0xE7) == 0x07) {
                        g |= groupLoadSegmentRegister;
                    }
                    groups_[i] = g;
                }
            }
        }

#if DEBUG_MC
        for (int i = 0; i < 256; i++) {
            std::cout << std::format("{:02X}:{:08X}\n", i, groups_[i]);
        }
#endif

        microcode_pointer_ = 0;
        microcode_return_ = 0;
    }

    void sanity_check() {
        if (byte_registers_[0] != reinterpret_cast<uint8_t*>(&registers_[24])) {
            std::cerr << "byte register pointers invalidated!" << std::endl;
        }
    }

    uint8_t queueRead(const QueueReadState qs) {
        const uint8_t value = prefetch_queue_.front();
        prefetch_queue_.pop_front();
        if (log_instructions_) {
            if (disassembler_.disassemble(value, qs == QueueReadState::FirstByte, disassembly_)) {
                InstructionHistoryEntry ihe;
                ihe.cs = cs();
                ihe.ip = inst_address_;
                ihe.disassembly = disassembly_;
                history_.push(ihe);
            }
        }
        dequeueing_ = true;
        next_queue_status_ = qs;
        next_queue_byte_ = value;
        return value;
    }

    int modRMReg() const { return (mod_rm_ >> 3) & 7; }
    int modRMReg2() const { return mod_rm_ & 7; }
    uint16_t& rw(const int r) { return registers_[24 + r]; }
    uint16_t& rw() { return rw(opcode_ & 7); }
    uint16_t& ax() { return rw(0); }
    uint8_t& rb(const int r) const { return *byte_registers_[r]; }
    uint8_t& al() const { return rb(0); }
    uint16_t& sr(const int r) { return registers_[r & 3]; }
    uint16_t& cs() { return sr(1); }

    // The carry flag is special and is gated by a latch to prevent it from being updated during certain instructions.
    // The group decode ROM output groupIncDec forces this latch low.
    // The carry latch starts low at microcode execution start so that EA calculations do not update the carry flag.
    // The RCY microcode operation can also set the carry latch low.
    void setAluCF(const bool v) {
        if (carry_latch_ && (group_ & groupIncDec) == 0) {
            carry_ = v;
        }
    }

    bool getAluCF() const { return carry_; }
    bool cf() { return lowBit(flags()); }
    void setCF(const bool v) { flags() = (flags() & ~1) | (v ? 1 : 0); }
    bool pf() { return (flags() & 4) != 0; }
    bool af() { return (flags() & 0x10) != 0; }
    bool zf() { return (flags() & 0x40) != 0; }
    bool sf() { return (flags() & 0x80) != 0; }
    bool intf() { return (flags() & 0x200) != 0; }
    void setIF(const bool v) { flags() = (flags() & ~0x200) | (v ? 0x200 : 0); }
    bool df() { return (flags() & 0x400) != 0; }
    void setDF(const bool v) { flags() = (flags() & ~0x400) | (v ? 0x400 : 0); }
    bool of() { return (flags() & 0x800) != 0; }
    void setOF(const bool v) { flags() = (flags() & ~0x800) | (v ? 0x800 : 0); }
    uint16_t& pc() { return registers_[4]; }
    uint16_t& ind() { return registers_[5]; }
    uint16_t& opr() { return registers_[6]; }
    uint16_t& tmpa() { return registers_[12]; }
    uint16_t& tmpb() { return registers_[13]; }
    uint16_t& flags() { return registers_[15]; }
    uint16_t& modRMRW() { return rw(modRMReg()); }
    uint8_t& modRMRB() { return rb(modRMReg()); }
    uint16_t& modRMRW2() { return rw(modRMReg2()); }
    uint8_t& modRMRB2() { return rb(modRMReg2()); }

    uint16_t getMemOrReg(bool mem) {
        if (mem) {
            if (use_memory_) {
                return opr();
            }
            if (!word_size_) {
                return modRMRB2();
            }
            return modRMRW2();
        }
        if ((group_ & groupNonSegregEA) == 0) {
            return sr(modRMReg());
        }
        if (!word_size_) {
            int n = modRMReg();
            uint16_t r = rw(n & 3);
            if ((n & 4) != 0) {
                r = (r >> 8) + (r << 8);
            }
            return r;
        }
        return modRMRW();
    }

    void setMemOrReg(bool mem, uint16_t v) {
        if (mem) {
            if (use_memory_) {
                opr() = v;
            }
            else {
                if (!word_size_) {
                    modRMRB2() = static_cast<uint8_t>(v);
                }
                else {
                    modRMRW2() = v;
                }
            }
        }
        else {
            if ((group_ & groupNonSegregEA) == 0) {
                sr(modRMReg()) = v;
            }
            else {
                if (!word_size_) {
                    modRMRB() = static_cast<uint8_t>(v);
                }
                else {
                    modRMRW() = v;
                }
            }
        }
    }

    void startInstruction() {
        if ((group_ & groupNonPrefix) != 0) {
            segment_override_ = -1;
            f1_ = false;
            repne_ = false;
            if (lock_) {
                lock_ = false;
                bus_.setLock(false);
            }
        }
        const auto new_opcode = next_microcode_pointer_ >> 4;

        checkOpcode(new_opcode);
        opcode_ = new_opcode;
        group_ = next_group_;
        // Count instruction starts, excluding prefixes and interrupt-entry microcode.
        // REP iterations execute within one instruction and do not increment this.
        if (new_opcode < 0x100 && (group_ & groupNonPrefix) != 0) {
            ++instruction_count_;
        }
    }

    void readFlags() {
        carry_ = cf();
        overflow_ = of();
        parity_ = pf() ? 0x04 : 0;
        sign_ = sf();
        zero_ = zf();
        auxiliary_ = af();
    }

    // Resolve the effective address calculation microcode address via the translation PLA, and set the effective base
    // segment accordingly.
    void lookupEACalculationAddress() {
        // The input to the translation PLA is 8 bits, 5 of which are from the ModR/M byte.
        // Bit 0 is don't care.
        // Bit 1 is always set for an EA lookup.
        // Bit 2 is don't care.
        // Bits 3-5 are ModRM bits 0-3 (RM field).
        // Bits 6-7 are ModRM bits 6-7 (Mod field).
        const int t = translation_[2 + ((mod_rm_ & 7) << 3) + (mod_rm_ & 0xc0)];
        // Bit 0 of the translation PLA output for an EA calculation address selects either DS or SS.
        segment_ = (lowBit(t) ? 2 : 3);
        // Save the return address and jump to EA calculation microcode. This takes one cycle.
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = t >> 1;
    }

    void startMicrocodeInstruction() {
        loader_state_ = 2;
        read_prefix_ = false;
        startInstruction();
        microcode_pointer_ = next_microcode_pointer_;
        word_size_ = true;
        if ((group_ & groupNoWidthInOpcodeBit0) == 0 && !lowBit(opcode_)) {
            word_size_ = false;
        }
        if ((group_ & groupByteOrWordAccess) == 0) {
            word_size_ = false; // Just for XLAT
        }
        readFlags();
        // Default is ADD tmpa (12) (assumed in EA calculations)
        alu_ = 0;
        alu_input_ = 0;
        m_is_m_ = ((group_ & groupNoDirectionBit) != 0 || (opcode_ & 2) == 0);
        rni_ = false;
        nx_ = false;
        skip_rni_ = false;
        state_ = stateRunning;

        if ((group_ & groupEffectiveAddress) != 0) {
            // This opcode has a ModR/M.

            // Disable the carry latch for EA calculation
            carry_latch_ = false;
            // EALOAD and EADONE finish with RTN
            mod_rm_ = next_mod_rm_;
            if ((group_ & groupMicrocodePointerFromOpcode) == 0) {
                microcode_pointer_ = ((mod_rm_ << 1) & 0x70) | 0xf00 | ((opcode_ & 1) << 12) | ((opcode_ & 8) << 4);
                state_ = stateSingleCycleWait;
            }
            // Check that RM != 11 (which would indicate a register-only operation)
            use_memory_ = ((mod_rm_ & 0xc0) != 0xc0);
            if (use_memory_) {
                // We have a memory operand - resolve the correct microcode address for EA calculation via the
                // translation PLA.
                lookupEACalculationAddress();
                state_ = stateSingleCycleWait;
            }
        }
    }

    // Not every instruction on the 8088 is microcoded - there are several small one-byte instructions that are
    // implemented in discrete logic. These include prefixes, the flag-twiddling opcodes, as most notoriously HLT.
    // We handle the logic for these here.
    // Since non-microcoded instructions don't have an RNI flag, we set the 'inst_boundary' flag when they complete.
    void startNonMicrocodeInstruction() {
        loader_state_ = 0;
        startInstruction();

        // Handle prefixes
        read_prefix_ = false;

        // LOCK prefix
        if ((group_ & groupLOCK) != 0) {
            locking_ = true;
            read_prefix_ = true;
            return;
        }
        // REP prefix
        if ((group_ & groupREP) != 0) {
            // REP prefix - set the F1 flag.

            // Internally, the F1 flag is overloaded to indicate both the presence of a REP prefix and the need to run
            // NEGATE for MUL/DIV instructions. This causes the interesting effect of inverting the product/quotient
            // when a REP prefix is used with MUL/DIV!
            f1_ = true;
            repne_ = !lowBit(opcode_);
            read_prefix_ = true;
            return;
        }
        if ((group_ & groupSegmentOverride) != 0) {
            segment_override_ = (opcode_ >> 3) & 3;
            read_prefix_ = true;
        }

        // Handle 1BL instructions
        if ((group_ & groupHLT) != 0) {
            loader_state_ = 2;
            rni_ = false;
            nx_ = false;
            state_ = stateHaltingStart;
            extra_halt_delay_ =
                !((bus_state_ == TState::TIdle && !t5_ && !t6_ && bus_status_ == BusStatus::Passive) ||
                  (t5_ && last_bus_status_ != BusStatus::InstructionFetch));
            return;
        }
        if ((group_ & groupCMC) != 0) {
            flags() ^= 1;
            inst_boundary_ = true;
            return;
        }
        if ((group_ & groupNonFlagSet) == 0) {
            switch (opcode_ & 0x06) {
                case 0: // CLCSTC
                    setCF(opcode_ & 1);
                    inst_boundary_ = true;
                    break;
                case 2: // CLISTI
                    setIF(opcode_ & 1);
                    inst_boundary_ = true;
                    break;
                case 4: // CLDSTD
                    setDF(opcode_ & 1);
                    inst_boundary_ = true;
                    break;
                default:
                    break;
            }
            return;
        }
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

    uint16_t doALU() {
        uint16_t t;
        const uint32_t a = registers_[alu_input_ + 12];
        uint32_t v = 0;
        switch (alu_) {
            case 0x00: // ADD
            case 0x02: // ADC
                return add(a, tmpb(), carry_ && alu_ != 0);
            case 0x01: // OR
                return bitwise(a | tmpb());
            case 0x03: // SBB
            case 0x05: // SUBT
            case 0x07: // CMP
                return sub(a, tmpb(), carry_ && alu_ == 3);
            case 0x04: // AND
                return bitwise(a & tmpb());
            case 0x06: // XOR
                return bitwise(a ^ tmpb());
            case 0x08: // ROL
                return doRotate((a << 1) | (topBit(a) ? 1 : 0), a, topBit(a));
            case 0x09: // ROR
                return doRotate(((a & wordMask()) >> 1) | topBit(lowBit(a)), a, lowBit(a));
            case 0x0a: // LRCY
                return doRotate((a << 1) | (carry_ ? 1 : 0), a, topBit(a));
            case 0x0b: // RRCY
                return doRotate(((a & wordMask()) >> 1) | topBit(carry_), a, lowBit(a));
            case 0x0c: // SHL
                return doShift(a << 1, a, topBit(a), (a & 0x08) != 0);
            case 0x0d: // SHR
                return doShift((a & wordMask()) >> 1, a, lowBit(a), false);
            case 0x0e: // SETMO
                return doSetmo();
            case 0x0f: // SAR
                return doShift(((a & wordMask()) >> 1) | topBit(topBit(a)), a, lowBit(a), false);
            case 0x10: // PASS
                // return doShift(a, a, false, false);
                return doPass(a);
            case 0x14: // DAA
                {
                    const auto al = static_cast<uint8_t>(a);
                    const bool low_gt9 = (al & 0x0f) > 9;

                    // Calculate CF before modifying AF.
                    carry_ = carry_ || (al >> 4) > 9 || ((al >> 4) == 9 && low_gt9 && !auxiliary_);
                    auxiliary_ = auxiliary_ || low_gt9;

                    v = (al + (auxiliary_ ? 0x06 : 0) + (carry_ ? 0x60 : 0)) & 0xff;
                    overflow_ = (al & 0x80) == 0 && (v & 0x80) != 0;
                    doPZS(v);
                    break;
                }
            case 0x15: // DAS
                carry_ = carry_ || a > (auxiliary_ ? 0x9fU : 0x99U);
                auxiliary_ = auxiliary_ || (a & 0x0f) > 9;

                v = a - (auxiliary_ ? 0x06 : 0) - (carry_ ? 0x60 : 0);
                overflow_ = (a & ~v & 0x80) != 0;
                doPZS(v);
                break;
            case 0x16: // AAA
                carry_ = (auxiliary_ || (a & 0xf) > 9);
                auxiliary_ = carry_;
                v = a + (carry_ ? 6 : 0);
                overflow_ = topBit(v & (v ^ a));
                doPZS(v);
                return v & 0x0f;
            case 0x17: // AAS
                carry_ = (auxiliary_ || (a & 0xf) > 9);
                auxiliary_ = carry_;
                v = a - (carry_ ? 6 : 0);
                overflow_ = topBit(a & (v ^ a));
                doPZS(v);
                return v & 0x0f;
            case 0x18: // INC
                v = a + 1;
                doPZS(v);
                overflow_ = topBit((v ^ a) & (v ^ 1));
                auxiliary_ = (((v ^ a ^ 1) & 0x10) != 0);
                break;
            case 0x19: // DEC
                v = a - 1;
                doPZS(v);
                overflow_ = topBit((a ^ 1) & (v ^ a));
                auxiliary_ = (((v ^ a ^ 1) & 0x10) != 0);
                break;
            case 0x1a: // COM1
                carry_ = false;
                overflow_ = false;
                return ~a;
            case 0x1b: // NEG
                return sub(0, a, false);
            case 0x1c: // INC2
                return a + 2; // flags never updated
            case 0x1d: // DEC2
                return a - 2; // flags never updated
            default:
                break;
        }
        return v;
    }

    void updateFlags() {
        flags() = (flags() & 0xf702) | (overflow_ ? 0x800 : 0) | (sign_ ? 0x80 : 0) | (zero_ ? 0x40 : 0) |
            (auxiliary_ ? 0x10 : 0) | parity_ // Already shifted
            | (carry_ ? 1 : 0);
    }

    uint32_t readSource() {
        uint32_t v;
        switch (source_) {
            case 7:
                { // Q
                    if (queue_bytes_ == 0) {
                        state_ = stateWaitingForQueueData;
                        return 0;
                    }
                    const uint8_t data = queueRead(QueueReadState::SubsequentByte);
                    checkSoftwareInterrupt(opcode_, data);
                    return data;
                }
            case 8: // A (AL)
            case 9: // C (CL)? - not used
            case 10: // E (DL)? - not used
            case 11: // L (BL)? - not used
                return rb(source_ & 3);
            case 16: // X (AH)
            case 17: // B (CH)? - not used
                return rb((source_ & 3) + 4);
            case 18: // M
                if ((group_ & groupMNotAccumulator) == 0) {
                    // This group decode ROM output forces M to use AL/AX.
                    return (word_size_ ? ax() : al());
                }
                if ((group_ & groupEffectiveAddress) == 0) {
                    return rw();
                }
                return getMemOrReg(m_is_m_);
            case 19: // R
                if ((group_ & groupEffectiveAddress) == 0) {
                    // This opcode has no ModR/M, so R is encoded in the opcode.
                    // This is used by PUSH/POP sreg instructions 06, 0E, 16, & 1E
                    return sr((opcode_ >> 3) & 7);
                }
                return getMemOrReg(!m_is_m_);
            case 20: // SIGMA
                v = doALU();
                if (update_flags_) {
                    updateFlags();
                }
                return v;
            case 22: // CR
                word_size_ = true; // HACK: not sure how this happens for INT0 on the hardware
                return microcode_pointer_ & 0xf;
            default:
                break;
        }
        return registers_[source_];
    }

    void writeDestination(const uint32_t v) {
        switch (destination_) {
            case 8: // A (AL)
            case 9: // C (CL)? - not used
            case 10: // E (DL)? - not used
            case 11: // L (BL)? - not used
                rb(destination_ & 3) = v;
                break;
            case 15: // F
                // Ensure our reserved flags are always set correctly
                flags() = (v & 0xFFD5) | 0xF002;
                break;
            case 16: // X (AH)
            case 17: // B (CH)? - not used
                rb((destination_ & 3) + 4) = v;
                break;
            case 18: // M
                if (alu_ == 7) {
                    // If ALU operation is CMP, we don't write back to M.
                    break;
                }
                if ((group_ & groupMNotAccumulator) == 0) {
                    // This opcode is fixed to use AL or AX.
                    if (!word_size_) {
                        al() = static_cast<uint8_t>(v);
                    }
                    else {
                        ax() = v;
                    }
                    break;
                }
                if ((group_ & groupEffectiveAddress) == 0) {
                    // Opcode has no ModR/M
                    if ((group_ & groupLoadRegisterImmediate) != 0 && (opcode_ & 8) == 0) {
                        // Write to a byte register
                        rb(opcode_ & 7) = v;
                    }
                    else if ((group_ & groupWidthInOpcodeBit3) != 0 && ((opcode_ & 8) != 0)) {
                        // Write to a byte register
                        rb(opcode_ & 7) = v;
                    }
                    else {
                        // Write to a word register
                        rw() = v;
                    }
                }
                else {
                    // Opcode has a ModR/M
                    setMemOrReg(m_is_m_, v);
                    skip_rni_ = m_is_m_ && use_memory_;
                }
                break;
            case 19: // R
                if ((group_ & groupEffectiveAddress) == 0) {
                    sr((opcode_ >> 3) & 7) = v;
                }
                else {
                    setMemOrReg(!m_is_m_, v);
                }
                break;
            case 20: // tmpaL
                tmpa() = (tmpa() & 0xff00) | (v & 0xff);
                break;
            case 21: // tmpbL - sign extend to tmpb
                tmpb() = ((v & 0x80) != 0 ? 0xff00 : 0) | (v & 0xff);
                break;
            case 22: // tmpaH
                tmpa() = (tmpa() & 0xff) | (v << 8);
                break;
            case 23: // tmpbH
                tmpb() = (tmpb() & 0xff) | (v << 8);
                break;
            default:
                if (destination_ < 32) {
                    registers_[destination_] = v;
                }
                else {
                    std::cerr << "Unknown destination: " << destination_ << std::endl;
                }
        }
    }

    void busAccessDone(const uint8_t high) {
        opr() |= high << 8;
        if ((operands_ & 0x10) != 0) {
            rni_ = true;
            in_instruction_ = false;
        }
        switch (operands_ & 3) {
            case 0: // Increment IND by 2
                ind() += 2;
                break;
            case 1: // Adjust IND according to word size and DF
                ind() += word_size_ ? (df() ? -2 : 2) : (df() ? -1 : 1);
                break;
            case 2: // Decrement IND by 2
                ind() -= 2;
                break;
            default:
                break;
        }
        state_ = stateRunning;
    }

    void doSecondMisc() {
        switch (operands_ & 7) {
            case 0: // RNI
                if (!skip_rni_) {
                    rni_ = true;
                    in_instruction_ = false;
                }
                break;
            case 1: // WB,NX
                if (!m_is_m_ || !use_memory_ || alu_ == 7) {
                    // Honor NX if M is R or ALU is CMP (no writeback)
                    nx_ = true;
                }
                break;
            case 2: // CORR
                state_ = stateWaitingForQueueIdle;
                break;
            case 3: // SUSP
                prefetching_ = false;
                if (bus_state_ != TState::T4 && bus_state_ != TState::TIdle) {
                    state_ = stateSuspending;
                    break;
                }
                bus_status_ = BusStatus::Passive;
                break;
            case 4: // RTN
                // Normal RTN updates carry?
                // std::cout << "Setting carry to " << carry_ << std::endl;
                setCF(carry_);

                microcode_pointer_ = microcode_return_;
                state_ = stateSingleCycleWait;
                break;
            case 5: // NX
                nx_ = true;
                break;
            default:
                break;
        }
    }

    void startIO() {
        state_ = stateIODelay1;
        if ((bus_state_ == TState::T3 || bus_state_ == TState::TWait) || canStartPrefetch()) {
            state_ = stateIODelay2;
        }
        if (bus_state_ == TState::T4 || bus_state_ == TState::TIdle) {
            bus_status_ = BusStatus::Passive;
        }
        io_requested_ = true;
    }

    void doSecondHalf() {
        switch (type_) {
            case 0: // short jump
                if (!condition(operands_ >> 4)) {
                    break;
                }
                microcode_pointer_ = (microcode_pointer_ & 0x1ff0) + (operands_ & 0xf);
                state_ = stateSingleCycleWait;
                break;
            case 1: // precondition ALU
                alu_ = operands_ >> 3;
                // Preconditioning the ALU unlocks the carry latch.
                carry_latch_ = true;
                nx_ = lowBit(operands_);
                if (m_is_m_ && use_memory_ && alu_ != 7 && (group_ & groupEffectiveAddress) != 0) {
                    nx_ = false;
                }
                alu_input_ = (operands_ >> 1) & 3;
                if (alu_ == 0x11) {
                    // XI
                    readFlags();
                    alu_ = ((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) |
                        ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10);
                }
                break;
            case 4:
                switch ((operands_ >> 3) & 0x0f) {
                    case 0: // MAXC
                        counter_ = word_size_ ? 15 : 7;
                        break;
                    case 1: // FLUSH
                        queue_bytes_ = 0;
                        prefetch_queue_.clear();
                        next_queue_status_ = QueueReadState::Flush;
                        queue_flushing_ = true;
                        break;
                    case 2: // CF1
                        f1_ = !f1_;
                        break;
                    case 3: // CITF
                        setIF(false);
                        flags() &= ~0x100;
                        break;
                    case 4: // RCY
                        carry_ = false;
                        carry_latch_ = false;
                        break;
                    case 6: // CCOF
                        carry_ = false;
                        setCF(false);
                        setOF(false);
                        break;
                    case 7: // SCOF
                        carry_ = true;
                        setCF(true);
                        setOF(true);
                        break;
                    case 8: // WAIT
                        // Don't know what this does!
                        break;
                    default:
                        break;
                }
                doSecondMisc();
                break;
            case 6:
                startIO();
                break;
            case 5: // long jump or call
            case 7:
                {
                    const int mc_ptr =
                        (((microcode_index_[microcode_pointer_ >> 2] << 2) + (microcode_pointer_ & 3)) << 2) >> 2;

                    // if (mc_ptr == 0x1c5) {
                    //     std::cout << "INT0: CF is " << (flags() & 1) << std::endl;
                    // }

                    if (!condition(operands_ >> 4)) {
                        break;
                    }
                    skip_rni_ = false;
                    if (type_ == 7) {
                        microcode_return_ = microcode_pointer_;
                    }
                    microcode_pointer_ =
                        translation_[((type_ & 2) << 6) + ((operands_ << 3) & 0x78) +
                                     ((group_ & groupInitialEARead) == 0 ? 4 : 0) + ((mod_rm_ & 0xc0) == 0 ? 1 : 0)] >>
                        1;

                    // int mc_ptr_dst =
                    // (((microcode_index_[microcode_pointer_ >> 2] << 2) +
                    //     (microcode_pointer_ & 3)) << 2) >> 2;
                    // std::cout << std::format("Long jump/call from {:03X} to {:03X}\n", mc_ptr, mc_ptr_dst);
                    state_ = stateSingleCycleWait;
                    break;
                }
            default:
                break;
        }
    }

    void busStart() {
        bool memory = (group_ & groupMemory) != 0;
        switch ((operands_ >> 5) & 3) {
            case 0:
                bus_status_ = memory ? BusStatus::MemoryRead : BusStatus::IoRead;
                break;
            case 1:
                bus_status_ = BusStatus::InterruptAcknowledge;
                break;
            case 2:
                bus_status_ = memory ? BusStatus::MemoryWrite : BusStatus::IoWrite;
                break;
            case 3:
                bus_status_ = BusStatus::Halt;
                break;
            default:
                break;
        }
    }


    // Main microcode execution function. Represents one cycle of the Execution Unit (EU).
    void executeMicrocode() {
        uint8_t* m;
        uint32_t v;

        switch (state_) {
            case stateRunning:
                last_microcode_pointer_ = microcode_pointer_;
                m = &microcode_[((microcode_index_[microcode_pointer_ >> 2] << 2) + (microcode_pointer_ & 3)) << 2];
                advanceMicrocodePointer();
                destination_ = m[0];
                source_ = m[1];
                // Mask off the F bit from the type field.
                type_ = m[2] & 7;
                // Unpack the F bit from the type field.
                update_flags_ = ((m[2] & 8) != 0);
                operands_ = m[3];
                v = readSource();
                if (state_ == stateWaitingForQueueData) {
                    // Empty queue prevents further execution.
                    break;
                }
                writeDestination(v);
                doSecondHalf();
                break;

            case stateWaitingForQueueData:
                if (queue_bytes_ == 0) {
                    // Still no data. Try again next cycle.
                    break;
                }
                // We have a byte in the queue, so resume running.
                state_ = stateRunning;
                // We can read the source now, so we can read it and immediately write back.
                writeDestination(readSource());
                // Process the operands part of the microcode word.
                doSecondHalf();
                break;

            case stateSuspending:
                if (bus_state_ != TState::T4) {
                    // Wait until any pending bus cycle is complete.
                    break;
                }
                state_ = stateRunning;
                break;

            case stateWaitingForQueueIdle:
                // This state is used by the CORR microcode operation.
                if (bus_status_ != BusStatus::Passive || bus_state_ == TState::T4 || t4_) {
                    break;
                }
                pc() -= queue_bytes_;
                queue_bytes_ = 0; // so that realIP() is correct
                state_ = stateRunning;
                break;

            case stateIODelay2:
                if (!ready_ && (bus_state_ == TState::T3 || bus_state_ == TState::TWait)) {
                    break;
                }
                state_ = stateIODelay1;
                break;

            case stateIODelay1:
                if (bus_state_ == TState::T4) {
                    break;
                }
                state_ = stateWaitingUntilFirstByteCanStart;
                break;

            case stateWaitingUntilFirstByteCanStart:
                {
                    if (bus_status_ != BusStatus::Passive) {
                        // Bus is busy
                        break;
                    }
                    io_write_data_ = opr() & 0xff;
                    io_segment_ = (operands_ >> 2) & 3;
                    auto base_segment = ((group_ & groupEffectiveAddress) != 0) ? segment_ : io_segment_;
                    if (io_segment_ == 3) {
                        // If segment is DS, use the segment override if present
                        io_segment_ = (segment_override_ != -1) ? segment_override_ : base_segment;
                    }
                    else {
                        // This is a no-segment access (IVT read or I/O).
                        // We use register slot 9 because it's a register slot that stays as all-zero bits, and has the
                        // same low two bits (so that the logs show the right segment).
                        if (io_segment_ == 1) {
                            io_segment_ = 9;
                        }
                    }
                    io_index_ = ind();
                    io_address_ = physicalAddress(io_segment_, io_index_);

                    state_ = stateWaitingUntilFirstByteDone;
                    busStart();
                    break;
                }
            case stateWaitingUntilFirstByteDone:
                if (!word_size_) {
                    // 8-bit access, disable BIU request flag as we will complete this bus cycle.
                    io_requested_ = false;
                }
                if (bus_status_ != BusStatus::Passive) {
                    // Bus is busy
                    break;
                }
                // Perform read or write
                io_write_data_ = opr() >> 8;
                opr() = io_read_data_;

                if (!word_size_) {
                    // 8-bit access - all done this state.
                    // When reading from the bus, the high byte is set to 0xFF on byte access.

                    // busAccessDone(0xFF);
                    busAccessDone(0x00);
                }
                else {
                    // 16-bit access - increment the address, start the second byte.
                    io_index_ = ind() + 1;
                    io_address_ = physicalAddress(io_segment_, io_index_);
                    state_ = stateWaitingUntilSecondByteDone;
                    busStart();
                }
                break;

            case stateWaitingUntilSecondByteDone:
                // Second half of a word-size transfer.
                io_requested_ = false;
                if (bus_status_ != BusStatus::Passive) {
                    // Bus is busy
                    break;
                }
                busAccessDone(io_read_data_);
                break;

            case stateSingleCycleWait:
                state_ = stateRunning;
                break;

            case stateHaltingStart:
                prefetching_ = false;
                state_ = stateHalting3;
                if (bus_status_ != BusStatus::Passive) {
                    break;
                }
                state_ = stateHalting2;
                break;

            case stateHalting3:
                if (bus_status_ != BusStatus::Passive) {
                    break;
                }
                state_ = stateHalting2;
                break;

            case stateHalting2:
                logger_.setStatus(BusStatus::Halt);
                state_ = stateHalting1;
                break;

            case stateHalting1:
                state_ = stateHalted;
                break;

            case stateHalted:
                // The CPU is halted!
                logger_.setStatus(BusStatus::Passive);
                // Stay halted until an interrupt occurs
                if (!interruptPending()) {
                    break;
                }
                // Try to account for a mysterious extra halt cycle
                if (extra_halt_delay_) {
                    extra_halt_delay_ = false;
                    break;
                }
                // Waking up now - read the next instruction
                rni_ = true;
                in_instruction_ = false;
                state_ = stateRunning;
                break;
        }
    }

    void setNextMicrocode(const int nextState, const int nextMicrocode) {
        next_microcode_pointer_ = nextMicrocode;
        loader_state_ = nextState | 1;
        next_group_ = groups_[nextMicrocode >> 4];
    }

    // Handles reading the next opcode byte.
    // The 8088 processes interrupts, traps and NMI at this point, so any of these states will prevent normal opcode
    // fetching.
    void readOpcode(const int nextState) {

        // Don't service interrupts after prefixes.
        if (!read_prefix_) {

            // Priority of servicing is NMI, interrupt, trap flag.
            // See https://www.righto.com/2023/02/8086-interrupt.html
            if (nmi_requested_) {
                nmi_requested_ = false;
                setNextMicrocode(nextState, 0x1001);
                return;
            }
            if (interruptPending()) {
                setNextMicrocode(nextState, 0x1002);
                return;
            }
            if ((flags() & 0x100) != 0) {
                // Trap flag is set.
                setNextMicrocode(nextState, 0x1000);
                return;
            }
        }

        // No interrupt conditions, so load the next opcode byte from the prefetch queue.
        if (queue_bytes_ != 0) {
            if (!in_instruction_) {
                // Starting a new instruction
                inst_boundary_ = true;
                in_instruction_ = true;
            }
            QueueEntry qe = {};
            prefetch_queue_.peekEntry(qe);
            inst_address_ = qe.address;
            setNextMicrocode(nextState, queueRead(QueueReadState::FirstByte) << 4);
            return;
        }
        loader_state_ = nextState & 2;
    }

    bool canStartPrefetch() {
        if (!prefetching_) { // prefetching turned off for a jump?
            return false;
        }
        if (io_requested_ || bus_status_ != BusStatus::Passive || t4_) { // bus busy?
            return false;
        }
        if (queue_filled_) {
            return false;
        }
        return true;
    }

    // Attempt to complete the current bus cycle. If the bus is not ready, return TWait to indicate we need to continue
    // waiting. Otherwise, complete the bus operation and return T4 to indicate the cycle is done.
    TState completeIO(const bool write) {
        if (!ready_) {
            return TState::TWait;
        }
        if (!write) {
            // Perform a bus read
            io_read_data_ = bus_.read();
            logger_.setData(io_read_data_);
        }
        else {
            // Perform a bus write
            io_read_data_ = io_write_data_;
        }
        bus_.setPassiveOrHalt(true);
        logger_.setStatus(BusStatus::Passive);
        last_bus_status_ = bus_status_;
        bus_status_ = BusStatus::Passive;
        return TState::T4;
    }

    // Execute one CPU cycle.
    void simulateCycle() {
        // QS pins report the queue operation performed during the previous cycle.
        queue_status_ = next_queue_status_;
        const auto queue_byte = next_queue_byte_;
        next_queue_status_ = QueueReadState::NoOperation;
        TState nextState = bus_state_;
        const bool write = bus_status_ == BusStatus::MemoryWrite || bus_status_ == BusStatus::IoWrite;
        t6_ = t5_;
        t5_ = t4_;
        t4_ = false;
        ready_ = bus_.ready();
        bool prefetchCompleting = false;
        switch (bus_state_) {
            case TState::T1:
                logger_.setCpuAddress(io_address_);
                bus_.startAccess(io_address_, bus_status_);
                nextState = TState::T2;
                break;
            case TState::T2:
                logger_.setStatusHigh(io_segment_);
                // The EU can prepare another transfer before this one's T4.
                // S4:S3 retain the segment latched on this transfer's T2.
                bus_segment_status_ = io_segment_ == 0 ? 0 : io_segment_ == 2 ? 1 : io_segment_ == 3 ? 3 : 2;
                logger_.setBusOperation(bus_status_);
                if (write) {
                    logger_.setData(io_write_data_);
                }
                if (bus_status_ == BusStatus::InterruptAcknowledge) {
                    bus_.setLock(state_ == stateWaitingUntilFirstByteDone);
                }
                nextState = TState::T3;
                break;
            case TState::T3:
                // This is a check for the prefetch delay policy.
                if (bus_status_ == BusStatus::InstructionFetch && queue_bytes_ == 3 && !dequeueing_) {
                    queue_filled_ = true;
                    //cycles_until_can_lower_queue_filled_ = 3;
                }
                nextState = completeIO(write);
                break;
            case TState::TWait:
                nextState = completeIO(write);
                break;
            case TState::T4:
                if (last_bus_status_ == BusStatus::MemoryWrite || last_bus_status_ == BusStatus::IoWrite) {
                    bus_.write(io_read_data_);
                }
                if (last_bus_status_ == BusStatus::InstructionFetch) {
                    prefetchCompleting = true;
                }
                nextState = TState::TIdle;
                t4_ = true;
                break;
            case TState::TIdle:
                break;
        }

        if (capture_bus_cycles_) {
            // Capture a CPU cycle snapshot for SST validation
            bus_cycle_ = {};
            bus_cycle_.phase = bus_state_;
            bus_cycle_.ale = bus_state_ == TState::T1;

            if (bus_state_ != TState::TIdle) {
                bus_cycle_.address = io_address_ & 0xfffff;
            }

            bus_cycle_.bus_status = static_cast<uint8_t>(
                (bus_state_ == TState::T1 || bus_state_ == TState::T2 ||
                 ((bus_state_ == TState::T3 || bus_state_ == TState::TWait) && !ready_))
                    ? bus_status_ : BusStatus::Passive);

            if (bus_state_ != TState::T1 && bus_state_ != TState::TIdle) {
                bus_cycle_.segment_status = bus_segment_status_;
            }

            const bool data_phase = bus_state_ == TState::T3 || bus_state_ == TState::TWait;
            const auto transfer = data_phase && ready_ ? last_bus_status_ : bus_status_;

            if (bus_state_ == TState::T2 || data_phase) {
                const uint8_t strobes = write ? (bus_state_ == TState::T2 ? 2 : 3) : 4;

                if (transfer == BusStatus::InstructionFetch || transfer == BusStatus::MemoryRead || transfer == BusStatus::MemoryWrite) {
                    bus_cycle_.memory_status = strobes;
                }
                else if (transfer == BusStatus::IoRead || transfer == BusStatus::IoWrite) {
                    bus_cycle_.io_status = strobes;
                }

                bus_cycle_.data_valid = data_phase && ready_;
                if (bus_cycle_.data_valid) {
                    bus_cycle_.data = io_read_data_;
                }
            }

            bus_cycle_.queue_status = queue_status_;
            bus_cycle_.queue_byte = queue_byte;
        }

        if (dequeueing_) {
            dequeueing_ = false;
            --queue_bytes_;
            // The ring was popped on the preceding EU clock; BIU bookkeeping follows now.
        }
        // if (cycles_until_can_lower_queue_filled_ == 0 || (cycles_until_can_lower_queue_filled_ == 1 && queue_bytes_ < 3)) {
        //cycles_until_can_lower_queue_filled_ = 0;
        if ((queue_bytes_ < 3 ||
             (bus_state_ == TState::TIdle && (last_bus_status_ != BusStatus::InstructionFetch || (!t4_ && !t5_))))) {
            if (bus_state_ == TState::TIdle &&
                !(t4_ && last_bus_status_ == BusStatus::InstructionFetch) && queue_bytes_ < 4) {
                queue_filled_ = false;
            }
        }
        //}
        // else
        //    --cycles_until_can_lower_queue_filled_;

        // We can execute microcode in loader states 2 & 3.
        if ((loader_state_ & 2) != 0) {
            executeMicrocode();
        }

        // Handle LOCK prefix.
        if (locking_) {
            locking_ = false;
            lock_ = true;
            bus_.setLock(true);
        }

        // Handle the instruction loader state machine.
        switch (loader_state_) {
            case 0:
                readOpcode(0);
                break;
            case 1:
            case 3:
                if ((group_ & groupNonPrefix) != 0) {
                    // A non-prefix byte was loaded.
                    // Clear any segment override, REP/REPE/REPNE, and LOCK state.
                    segment_override_ = -1;
                    f1_ = false;
                    repne_ = false;
                    // Clear any previous lock condition.
                    if (lock_) {
                        lock_ = false;
                        bus_.setLock(false);
                    }
                }
                if ((next_group_ & groupMicrocoded) == 0) {
                    // 1BL
                    startNonMicrocodeInstruction();
                }
                else {
                    if ((next_group_ & groupEffectiveAddress) == 0) {
                        // SC
                        startMicrocodeInstruction();
                    }
                    else {
                        loader_state_ = 1;
                        if (queue_bytes_ != 0) {
                            // SC
                            next_mod_rm_ = queueRead(QueueReadState::SubsequentByte);
                            startMicrocodeInstruction();
                        }
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
            default:
                break;
        }

        // If we just completed a prefetch, add the byte to the queue.
        if (prefetchCompleting) {
            prefetch_queue_.push_word(static_cast<WordT>(io_read_data_), pc());
            ++queue_bytes_;
            ++pc();
        }

        if (nextState == TState::TIdle && bus_status_ != BusStatus::Passive) {
            nextState = TState::T1;
            if (bus_status_ == BusStatus::InstructionFetch) {
                io_index_ = pc();
                io_address_ = physicalAddress(io_segment_, pc());
            }

            bus_.setPassiveOrHalt(bus_status_ == BusStatus::Halt);
            logger_.setStatus(bus_status_);
        }
        if (canStartPrefetch()) {
            bus_status_ = BusStatus::InstructionFetch;
            io_segment_ = 1;
        }
        if (queue_flushing_) {
            queue_flushing_ = false;
            prefetching_ = true;
        }
        // If cycle logging is enabled we want to capture logs regardless of the configured end cycle.
        if (cycle_logging_ && cycle_ < log_end_cycle_) {
            logger_.setAEN(bus_.getAEN());
            logger_.setDMA(bus_.getDMA());
            logger_.setPITBits(bus_.pitBits());
            logger_.setBusOperation(bus_.getBusOperation());
            logger_.setInterruptFlag(intf());
            if (bus_.getDMAS3()) {
                logger_.setDmaAddress(bus_.getDMAAddress());
            }
            else if (bus_.getDMADelayedT2()) {
                logger_.restoreCpuAddress();
                logger_.setBusOperation(bus_status_);
            }
            logger_.setReady(ready_);
            logger_.setLock(lock_);
            logger_.setDMAS(bus_.getDMAS());
            logger_.setIRQs(bus_.getIRQLines());
            logger_.setINT(bus_.interruptPending());
            //logger_.setCGA(bus_.getCGA());

            if (defer_cycle_log_ && !console_logging_) {
                // Save only the cycles that can survive this frame's rolling log.
                // The live logger still advances so bus and disassembly state stay exact.
                if (cycle_ >= log_start_cycle_ && log_capacity_ != 0) {
                    if (deferred_cycle_log_.size() == log_capacity_) {
                        deferred_cycle_log_.pop_front();
                    }
                    deferred_cycle_log_.push_back({logger_, prefetch_queue_, queue_status_, queue_byte,
                                                 currentMicrocodeLogState()});
                }
                last_microcode_pointer_ = -1;
                logger_.advance(queue_status_, queue_byte);
            } else {
                CycleLogEntry entry{logger_.getLine(prefetch_queue_, queue_status_, queue_byte),
                                    currentMicrocodeLogState()};
                last_microcode_pointer_ = -1;
                if (cycle_ >= log_start_cycle_) {
                    if (console_logging_) {
                        std::string line;
                        formatCycleLogEntry(entry, line);
                        std::cout << line << std::endl;
                    }
                    appendCycleLogEntry(std::move(entry));
                }
            }
        }
        bus_state_ = nextState;
        ++cycle_;
        interrupt_pending_ = bus_.interruptPending();
        bus_.tick();
    }

    std::optional<CycleLogMicrocodeState> currentMicrocodeLogState() {
        if (last_microcode_pointer_ < 0) {
            return std::nullopt;
        }
        return CycleLogMicrocodeState{static_cast<uint16_t>(last_microcode_pointer_), getAluCF(), cf(),
                                     registers_[12], registers_[13], registers_[14], word_size_};
    }

    // Evaluate a microcode condition field. Usually these are used to determine whether to take a jump/call.
    bool condition(const int n) {
        switch (n) {
            case 0x00: // F1ZZ - compare F1 to ZF
                if ((group_ & groupF1ZZFromPrefix) != 0) {
                    return zf() == (f1_ && repne_);
                }
                return zf() != lowBit(opcode_);
            case 0x01: // MOD1 - If one byte displacement (skips second queue read).
                return (mod_rm_ & 0x40) != 0;
            case 0x02: // L8 - not sure if there's a better way to compute this
                if ((group_ & groupLoadRegisterImmediate) != 0) {
                    return (opcode_ & 8) == 0;
                }
                return !lowBit(opcode_) || (opcode_ & 6) == 2;
            case 0x03: // Z - if zero flag set
                return super_zero_;
            case 0x04: // NCZ - Decrement count register, true if not zero
                --counter_;
                return counter_ != -1;
            case 0x05: // TEST - no 8087 emulated yet
                return true;
            case 0x06: // OF - if overflow flag set
                return of(); // only used in INTO
            case 0x07: // CY - if carry set
                return carry_;
            case 0x08: // UNC - Unconditional. Always true.
                return true;
            case 0x09: // NF1 - if F1 flag not set
                return !f1_;
            case 0x0a: // NZ - if zero flag not set
                return !super_zero_;
            case 0x0b: // X0 - if bit 3 of opcode/extension is set
                if ((group_ & groupMicrocodePointerFromOpcode) == 0) {
                    // Extension; use ModR/M instead of opcode.
                    return (mod_rm_ & 8) != 0;
                }
                // Non-extension; use opcode.
                return (opcode_ & 8) != 0;
            case 0x0c: // NCY - if carry not set
                return !carry_;
            case 0x0d: // F1 - if F1 flag is set (REP prefix or signed multiply/divide)
                return f1_;
            case 0x0e: // INT - if interrupt pending
                return interruptPending();
            default:
                break;
        }
        bool jump = false; // XC
        switch (opcode_ & 0x0e) {
            case 0x00:
                jump = of();
                break; // O
            case 0x02:
                jump = cf();
                break; // C
            case 0x04:
                jump = zf();
                break; // Z
            case 0x06:
                jump = cf() || zf();
                break; // BE
            case 0x08:
                jump = sf();
                break; // S
            case 0x0a:
                jump = pf();
                break; // P
            case 0x0c:
                jump = (sf() != of());
                break; // L
            case 0x0e:
                jump = (sf() != of()) || zf();
                break; // LE
            default:
                break;
        }
        if (lowBit(opcode_)) {
            jump = !jump;
        }
        return jump;
    }

    bool interruptPending() { return nmi_requested_ || (intf() && interrupt_pending_); }

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

    // Calculate physical address from segment and offset, masking to 20 bits
    uint32_t physicalAddress(const int segment, const uint16_t offset) const {
        return ((registers_[segment] << 4) + offset) & 0xFFFFF;
    }

    std::string log_;
    // Ring buffer of recent cycles; microcode text is resolved only when displayed.
    std::deque<CycleLogEntry> log_buffer_;
    // Tracks committed buffer changes, including replacement at capacity; survives reset.
    uint64_t cycle_log_revision_ = 0;
    size_t log_capacity_ = 1000; // default capacity (lines)
    bool cycle_logging_ = false; // enabled via GUI
    struct DeferredCycleLog {
        Logger logger;
        cpu::PrefetchQueue<QueueLen> queue;
        QueueReadState queue_status;
        uint8_t queue_byte;
        std::optional<CycleLogMicrocodeState> microcode;
    };
    std::deque<DeferredCycleLog> deferred_cycle_log_;
    bool defer_cycle_log_ = false;
    BusType bus_;

    void appendCycleLogEntry(CycleLogEntry entry) {
        if (log_capacity_ == 0) {
            return;
        }
        if (log_buffer_.size() == log_capacity_) {
            log_buffer_.pop_front();
        }
        log_buffer_.push_back(std::move(entry));
        ++cycle_log_revision_;
    }

public:
    // Cycle log API
    void setCycleLogging(bool v) {
        if (v && !cycle_logging_) {
            logger_.beginLogging();
        }
        cycle_logging_ = v;
    }
    void beginCycleLogFrame() {
        defer_cycle_log_ = cycle_logging_ && !console_logging_;
        deferred_cycle_log_.clear();
    }
    void endCycleLogFrame() {
        for (auto& cycle : deferred_cycle_log_) {
            appendCycleLogEntry({cycle.logger.getLine(cycle.queue, cycle.queue_status, cycle.queue_byte),
                                 cycle.microcode});
        }
        deferred_cycle_log_.clear();
        defer_cycle_log_ = false;
    }
    bool isCycleLogging() const { return cycle_logging_; }
    void clearCycleLog() {
        if (!log_buffer_.empty()) {
            ++cycle_log_revision_;
        }
        log_buffer_.clear();
        deferred_cycle_log_.clear();
    }

    void setCycleLogCapacity(size_t c) {
        log_capacity_ = c;
        if (log_buffer_.size() > log_capacity_) {
            ++cycle_log_revision_;
        }
        while (deferred_cycle_log_.size() > log_capacity_) {
            deferred_cycle_log_.pop_front();
        }
        while (log_buffer_.size() > log_capacity_) {
            log_buffer_.pop_front();
        }
    }

    const std::deque<CycleLogEntry>& getCycleLogBuffer() const { return log_buffer_; }
    size_t getCycleLogSize() const { return log_buffer_.size(); }
    uint64_t getCycleLogRevision() const { return cycle_log_revision_; }
    size_t getCycleLogCapacity() const { return log_capacity_; }
    // Append a single line directly into the cycle log buffer (for diagnostics/UI)
    void appendCycleLogLine(std::string line) {
        appendCycleLogEntry({std::move(line), std::nullopt});
    }
    std::string_view getMicrocodeDisassembly(uint16_t address) const {
        return CycleLogMicrocode::disassembly(address, std::is_same_v<WordT, uint16_t>);
    }
    void formatCycleLogEntry(const CycleLogEntry& entry, std::string& line) const {
        CycleLogMicrocode::format(entry, entry.microcode ? getMicrocodeDisassembly(entry.microcode->address)
                                                       : std::string_view{}, line);
    }

    std::string getQueueString() const {
        std::string result;
        for (auto byte : prefetch_queue_) {
            result += std::format("{:02X}", byte);
        }
        return result;
    }

    std::string getQueueDebugString() const {
        std::string result;
        for (std::size_t i = 0; i < prefetch_queue_.size(); ++i) {
            const auto& entry = prefetch_queue_.entry(i);
            result += std::format("{:02X}[{:04X}] ", entry.data, entry.address);
        }
        return result;
    }

private:
    using InstructionQueue = cpu::PrefetchQueue<QueueLen>;

    class InstructionHistory
    {
    public:
        typedef std::size_t size_type;

        InstructionHistory() : head_(0), tail_(0), size_(0) {}

        void clear() {
            head_ = 0;
            tail_ = 0;
            size_ = 0;
        }

        [[nodiscard]] size_type len() const { return size_; }

        [[nodiscard]] size_type capacity() const { return capacity_; }

        [[nodiscard]] bool isEmpty() const { return size_ == 0; }

        [[nodiscard]] bool full() const { return head_ == tail_; }

        [[nodiscard]] size_type freeSpace() const { return QueueLen - size_; }

        [[nodiscard]] bool hasRoom() const { return freeSpace() >= sizeof(WordT); }

        // Push a single entry (byte + address). Returns false if full.
        bool push(InstructionHistoryEntry entry) {
            if (full()) {
                pop();
            }
            buffer_[head_] = entry;
            advanceHead();
            return true;
        }

        bool pop() {
            if (isEmpty()) {
                return false;
            }
            advanceTail();
            return true;
        }

        // Pop oldest entry. Returns false if empty.
        bool pop(InstructionHistoryEntry& out) {
            if (isEmpty()) {
                return false;
            }
            out = buffer_[tail_];
            advanceTail();
            return true;
        }

        // Peek the newest entry without removing it. Returns false if empty.
        bool peekEntry(InstructionHistoryEntry& out) const {
            if (isEmpty()) {
                return false;
            }
            out = buffer_[head_];
            return true;
        }

        std::vector<InstructionHistoryEntry> getLast(size_t lines) const {
            std::vector<InstructionHistoryEntry> out;
            if (isEmpty()) {
                return out; // nothing to return
            }
            // Clamp requested lines to number of valid entries
            if (lines > size_) {
                lines = size_;
            }
            out.reserve(lines);

            // Start from the most recently written entry (head_ points to next write slot)
            size_type index = (head_ == 0 ? capacity_ - 1 : head_ - 1);

            for (size_t count = 0; count < lines; ++count) {
                out.push_back(buffer_[index]);
                // If we've reached the oldest entry, stop early.
                if (index == tail_) {
                    break;
                }
                // Move backward with wrap-around
                index = (index == 0 ? capacity_ - 1 : index - 1);
            }

            return out;
        }

    private:
        std::array<InstructionHistoryEntry, 1000> buffer_;
        size_type capacity_ = 1000;
        size_type head_; // next write
        size_type tail_; // next read
        size_type size_; // number of valid entries

        void advanceHead() {
            head_ = (head_ + 1) % capacity_;
            ++size_;
        }

        void advanceTail() {
            tail_ = (tail_ + 1) % capacity_;
            --size_;
        }
    };

    // Advance the microcode pointer to the next instruction. Only the low 4 bits are incremented.
    void advanceMicrocodePointer() {
        microcode_pointer_ = (microcode_pointer_ & 0xFFF0) | ((microcode_pointer_ + 1) & 0xf);
    }

    int stop_ip_;
    int stop_seg_;

    uint64_t cycle_;
    uint64_t log_start_cycle_;
    uint64_t log_end_cycle_ = UINT64_MAX;
    uint64_t execute_end_cycle_;
    bool console_logging_;

    bool nmi_requested_; // Not actually set anywhere yet

    TState bus_state_;
    bool prefetching_;

    BusStatus bus_status_;
    uint32_t io_address_;
    uint16_t io_index_;
    uint8_t io_read_data_;
    uint8_t io_write_data_;
    int io_segment_;
    BusStatus last_bus_status_;

    Logger logger_;

    uint16_t registers_[32];
    InstructionQueue prefetch_queue_{};
    int queue_bytes_;
    uint8_t* byte_registers_[8];
    uint8_t microcode_[4 * 512];
    uint8_t microcode_index_[2048];
    uint16_t translation_[256];
    uint32_t groups_[257];
    uint32_t group_;
    uint32_t next_group_;
    uint16_t microcode_pointer_;
    uint16_t next_microcode_pointer_;
    uint16_t microcode_return_;
    int counter_; // only 4 bits on the CPU
    uint8_t alu_;
    int segment_override_;
    bool f1_;
    bool repne_;
    bool lock_;
    uint8_t opcode_;
    uint8_t mod_rm_;
    bool carry_{false};
    bool carry_latch_{false}; // This latch enables updating the carry flag.
    bool zero_{false};
    bool super_zero_{false};
    bool auxiliary_{false};
    bool sign_{false};
    uint8_t parity_{0};
    bool overflow_{false};
    int alu_input_;
    uint8_t next_mod_rm_;
    int loader_state_;
    bool rni_{false}; // Microcode signal to read next instruction
    uint16_t inst_address_{0x0000};
    uint64_t instruction_count_{0};
    bool inst_boundary_{false};
    bool in_instruction_{false};
    QueueReadState queue_status_{QueueReadState::NoOperation};
    QueueReadState next_queue_status_{QueueReadState::NoOperation};
    uint8_t next_queue_byte_ = 0;
    bool capture_bus_cycles_ = false;
    CpuBusCycle bus_cycle_{};
    uint8_t bus_segment_status_ = 4;
    bool nx_{false}; // Microcode signal to read next instruction early (1-cycle pipeline)
    MicrocodeState state_;
    int source_;
    int destination_;
    int type_;
    bool update_flags_{false};
    uint8_t operands_;
    bool m_is_m_;
    bool skip_rni_;
    bool use_memory_;
    bool read_prefix_{false};
    bool word_size_;
    int segment_;
    int last_microcode_pointer_;
    bool dequeueing_;
    int io_cancelling_;
    bool io_requested_;
    bool t4_;
    bool t5_;
    bool t6_;
    bool prefetch_delayed_;
    bool queue_flushing_;
    bool queue_filled_;
    bool interrupt_pending_;
    bool extra_halt_delay_;
    bool ready_ = true;
    // int cycles_until_can_lower_queue_filled_;
    bool locking_ = false;
    uint32_t test_number_ = 0;

    bool log_instructions_ = false;
    std::string disassembly_;
    InstructionHistory history_;
    Disassembler disassembler_;
};

#endif
