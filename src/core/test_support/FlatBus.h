// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>
#include "../cpu_types.h"

namespace marty::testing
{

struct BusAccess
{
    uint32_t address;
    uint8_t value;
    bool write, port;
};

namespace detail
{

template <bool Enabled>
struct BusActivity
{
};

template <>
struct BusActivity<true>
{
    std::vector<BusAccess> accesses;
    bool capture = false, irq = false, locked = false, passive = true;
    uint64_t ticks = 0;
};

} // namespace detail

// Shared test memory and bus behavior.
// The untracked template specialization does not record bus activity.
// CPU interfaces are adapted separately
template <bool TrackActivity>
class BasicFlatBus : public detail::BusActivity<TrackActivity>
{
    const std::vector<uint8_t>* instruction_stream_ = nullptr;
    size_t stream_cursor_ = 0;

public:
    using Access = BusAccess;
    std::vector<uint8_t> memory;

private:
    std::optional<size_t> instruction_fetch_bytes_;

public:
    uint32_t address = 0;
    BusStatus bus_status = BusStatus::Passive;

    BasicFlatBus() : memory(1 << 20, 0) {}

    uint8_t* ram() { return memory.data(); }
    [[nodiscard]] const uint8_t* ram() const { return memory.data(); }
    [[nodiscard]] size_t ramSize() const { return memory.size(); }
    void setMemory(const uint32_t a, const uint8_t value) { memory[a & 0xfffff] = value; }

    // Count only bytes still to be fetched, excluding the initial queue.
    void setInstructionFetchBytes(size_t remaining) { instruction_fetch_bytes_ = remaining; }

    // Borrow input bytes, then supply NOPs independently of fetch addresses.
    // The vector must remain alive until reset/clearInstructionFetch. A stream
    // takes precedence over the RAM-byte allowance, matching the SST harness.
    void setInstructionStream(const std::vector<uint8_t>& bytes, size_t prefetched) {
        instruction_stream_ = &bytes;
        stream_cursor_ = prefetched;
    }

    void clearInstructionFetch() {
        instruction_stream_ = nullptr;
        stream_cursor_ = 0;
        instruction_fetch_bytes_.reset();
    }

    // Memory wraps at 20 bits; I/O addresses at 16.
    void startAccess(uint32_t a, BusStatus bus_status) {
        address = a;
        this->bus_status = bus_status;
    }

    bool ready() const { return true; }
    [[nodiscard]] bool interruptPending() const {
        if constexpr (TrackActivity) {
            return this->irq;
        }
        return false;
    }

    void setLock(bool value) {
        if constexpr (TrackActivity) {
            this->locked = value;
        }
    }

    void setPassiveOrHalt(bool value) {
        if constexpr (TrackActivity) {
            this->passive = value;
        }
    }

    void tick() {
        if constexpr (TrackActivity) {
            ++this->ticks;
        }
    }

    [[nodiscard]] uint32_t byteAddress(const unsigned lane) const {
        const bool io = bus_status == BusStatus::InterruptAcknowledge ||
                        bus_status == BusStatus::IoRead || bus_status == BusStatus::IoWrite;
        return (address + lane) & (io ? 0xffff : 0xfffff);
    }

    // The byte adapter uses these directly. Compute a RAM address only once
    // stream/allowance policies have decided the byte actually comes from RAM.
    // As in XTCE's byte interface, the method selects transfer direction and
    // the bus status selects memory versus I/O.
    uint8_t readByte(const unsigned lane = 0) {
        uint8_t value = 0xff;
        if (bus_status == BusStatus::InstructionFetch || bus_status == BusStatus::MemoryRead ||
            bus_status == BusStatus::MemoryWrite) {
            if (bus_status == BusStatus::InstructionFetch && instruction_stream_) {
                return stream_cursor_ < instruction_stream_->size() ? (*instruction_stream_)[stream_cursor_++] : 0x90;
            }
            if (bus_status == BusStatus::InstructionFetch && instruction_fetch_bytes_) {
                if (*instruction_fetch_bytes_ == 0) {
                    return 0x90;
                }
                --*instruction_fetch_bytes_;
            }
            value = memory[(address + lane) & 0xfffff];
        }

        if constexpr (TrackActivity) {
            if (this->capture && bus_status != BusStatus::InstructionFetch) {
                this->accesses.push_back({byteAddress(lane), value, false, bus_status == BusStatus::IoRead});
            }
        }

        return value;
    }
    void writeByte(uint8_t value, unsigned lane = 0) {
        if (bus_status == BusStatus::InstructionFetch || bus_status == BusStatus::MemoryRead ||
            bus_status == BusStatus::MemoryWrite) {
            setMemory(address + lane, value);
        }
        if constexpr (TrackActivity) {
            if (this->capture) {
                this->accesses.push_back({byteAddress(lane), value, true, bus_status == BusStatus::IoWrite});
            }
        }
    }

    template <unsigned Bytes>
    uint16_t readTransfer() {
        static_assert(Bytes == 1 || Bytes == 2);
        uint16_t value = 0;
        for (unsigned lane = 0; lane < Bytes; ++lane) {
            value |= static_cast<uint16_t>(readByte(lane)) << (lane * 8);
        }
        return value;
    }

    template <unsigned Bytes>
    void writeTransfer(const uint16_t value) {
        static_assert(Bytes == 1 || Bytes == 2);
        for (unsigned lane = 0; lane < Bytes; ++lane) {
            writeByte(static_cast<uint8_t>(value >> (lane * 8)), lane);
        }
    }

    void reset() {
        std::fill(memory.begin(), memory.end(), 0);
        clearInstructionFetch();
        address = 0;
        bus_status = BusStatus::Passive;
        if constexpr (TrackActivity) {
            this->accesses.clear();
            this->capture = this->irq = this->locked = false;
            this->passive = true;
            this->ticks = 0;
        }
    }
};

// Standalone CPU host: each access selects a byte or word transfer. XTCE's
// byte-only adapter uses BasicFlatBus directly and needs no width state.
template <bool TrackActivity>
struct TransferBus : BasicFlatBus<TrackActivity>
{

    unsigned width = 1;

    void startAccess(uint32_t address, BusStatus bus_status, const unsigned bytes) {
        assert(bytes == 1 || bytes == 2);
        BasicFlatBus<TrackActivity>::startAccess(address, bus_status);
        width = bytes;
    }

    uint16_t read() { return width == 1 ? this->template readTransfer<1>() : this->template readTransfer<2>(); }

    void write(uint16_t value) {
        if (width == 1) {
            this->template writeTransfer<1>(value);
        }
        else {
            this->template writeTransfer<2>(value);
        }
    }

    void reset() {
        BasicFlatBus<TrackActivity>::reset();
        width = 1;
    }
};

using FlatBus = TransferBus<true>;

} // namespace marty::testing
