// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once
#include <cstdint>

namespace cpu
{

// Shared execution controls.
// Both cores check these at the corresponding CPU event and stop after completing.
class ExecutionControl
{
public:
    enum class RunResult
    {
        Ok,
        Halt,
        BreakpointHit,
        OffRails
    };

    void setBreakpoint(const uint16_t cs, const uint16_t ip) {
        breakpoint_cs_ = cs;
        breakpoint_ip_ = ip;
        has_breakpoint_ = true;
        breakpoint_hit_ = false;
    }
    void clearBreakpoint() { has_breakpoint_ = breakpoint_hit_ = false; }
    [[nodiscard]] bool hasBreakpoint() const { return has_breakpoint_; }
    [[nodiscard]] bool breakpointHit() const { return breakpoint_hit_; }
    [[nodiscard]] uint16_t breakpointCS() const { return breakpoint_cs_; }
    [[nodiscard]] uint16_t breakpointIP() const { return breakpoint_ip_; }
    void clearBreakpointHit() { breakpoint_hit_ = false; }

    void setSoftwareInterruptBreakpoint(const uint8_t vector) {
        software_interrupt_breakpoint_ = vector;
        breakpoint_hit_ = false;
    }
    void clearSoftwareInterruptBreakpoint() { software_interrupt_breakpoint_ = -1; }

    void setOffRailsDetection(const bool enabled, const int maximum = 20) {
        off_rails_detection_ = enabled;
        bad_opcode_max_ = maximum;
        bad_opcode_ct_ = 0;
        last_opcode_ = -1;
        off_rails_ = false;
    }

    void beginRun() {
        breakpoint_hit_ = false;
        off_rails_ = false;
    }
    [[nodiscard]] bool executionStopped() const { return breakpoint_hit_ || off_rails_; }
    [[nodiscard]] RunResult stopReason() const {
        if (breakpoint_hit_) {
            return RunResult::BreakpointHit;
        }
        if (off_rails_) {
            return RunResult::OffRails;
        }
        return RunResult::Ok;
    }

protected:
    void resetExecutionControl() {
        beginRun();
        bad_opcode_ct_ = 0;
        last_opcode_ = -1;
    }

    void checkExecutionBreakpoint(const uint16_t cs, const uint16_t ip) {
        if (has_breakpoint_ && cs == breakpoint_cs_ && ip == breakpoint_ip_) {
            breakpoint_hit_ = true;
        }
    }

    void checkSoftwareInterrupt(const int opcode, const uint8_t vector) {
        if (opcode == 0xcd && vector == software_interrupt_breakpoint_) {
            breakpoint_hit_ = true;
        }
    }

    void checkOpcode(const int opcode) {
        if (!off_rails_detection_) {
            return;
        }
        const bool suspicious = opcode == 0 || opcode == 0xff;
        bad_opcode_ct_ = suspicious ? (opcode == last_opcode_ ? bad_opcode_ct_ + 1 : 1) : 0;
        last_opcode_ = opcode;
        if (bad_opcode_ct_ >= bad_opcode_max_) {
            off_rails_ = true;
        }
    }

    bool has_breakpoint_ = false, breakpoint_hit_ = false;
    uint16_t breakpoint_cs_ = 0, breakpoint_ip_ = 0;
    int software_interrupt_breakpoint_ = -1;
    bool off_rails_detection_ = false, off_rails_ = false;
    int bad_opcode_max_ = 20, bad_opcode_ct_ = 0;
    int last_opcode_ = -1;
};

} // namespace cpu
