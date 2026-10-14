// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once
#include "test_support/FlatBus.h"

// XTCE byte-bus adapter over shared test memory and fetch policies.
// Activity collection is compiled out for ordinary CPU tests and benchmarks.
struct StubBus : marty::testing::BasicFlatBus<false> {
    StubBus() { bus_status = BusStatus::InterruptAcknowledge; }
    uint8_t read() { return readByte(); }
    void write(uint8_t value) { writeByte(value); }
    void reset() { BasicFlatBus::reset(); bus_status = BusStatus::InterruptAcknowledge; }

    bool getAEN() const { return false; }
    bool getDMA() const { return false; }
    int getDMAS() const { return 0; }
    bool getDMAS3() const { return false; }
    uint32_t getDMAAddress() const { return 0; }
    bool getDMADelayedT2() const { return false; }
    uint8_t pitBits() const { return 0; }
    BusStatus getBusOperation() const { return BusStatus::Passive; }
    uint32_t getIRQLines() const { return 0; }
    void stubInit() {}
};
