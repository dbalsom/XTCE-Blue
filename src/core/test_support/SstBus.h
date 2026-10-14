// SPDX-License-Identifier: MIT
#pragma once
#include "FlatBus.h"

// Shared SST adapter: retain ordered operand and I/O accesses for every core.
struct SstBus : marty::testing::BasicFlatBus<true> {
    uint8_t read() { return readByte(); }
    void write(uint8_t value) { writeByte(value); }

    // No motherboard devices are attached. These signals feed Intel diagnostics.
    bool getAEN() const { return false; }
    bool getDMA() const { return false; }
    int getDMAS() const { return 0; }
    bool getDMAS3() const { return false; }
    uint32_t getDMAAddress() const { return 0; }
    bool getDMADelayedT2() const { return false; }
    uint8_t pitBits() const { return 0; }
    BusStatus getBusOperation() const { return bus_status; }
    uint32_t getIRQLines() const { return 0; }
    void stubInit() {}
};
