// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>

namespace cpu {

struct PrefetchEntry {
    uint8_t data = 0;
    uint16_t address = 0; // IP at which this byte was fetched, including wraparound.
};

// Shared storage for interpreted and generated CPUs. Queue capacity, fetch
// width, fill policy, and the delayed BIU byte count remain CPU responsibilities.
// Both bytes and fetch addresses survive wrapping and value copies; hot-path
// operations neither allocate nor dispatch through a virtual interface.
template<std::size_t Capacity>
class PrefetchQueue {
    static_assert(Capacity > 0, "Prefetch queue capacity must be positive");
public:
    static constexpr std::size_t capacity = Capacity;
    using Entry = PrefetchEntry;

    bool empty() const { return count_ == 0; }
    bool full() const { return count_ == Capacity; }
    std::size_t size() const { return count_; }
    std::size_t freeSpace() const { return Capacity - count_; }

    const Entry& entry(std::size_t offset) const {
        assert(offset < count_);
        return entries_[index(offset)];
    }
    const uint8_t& operator[](std::size_t offset) const { return entry(offset).data; }
    const uint8_t& front() const { return (*this)[0]; }

    void push_back(uint8_t value, uint16_t address = 0) {
        assert(!full());
        entries_[index(count_)] = {value, address};
        ++count_;
    }

    // A native bus word is appended atomically in little-endian byte order.
    // Insufficient space leaves the queue untouched.
    template<class Word> bool push_word(Word word, uint16_t address) {
        static_assert(std::is_same_v<Word, uint8_t> || std::is_same_v<Word, uint16_t>,
                      "Prefetch words must be uint8_t or uint16_t");
        if (freeSpace() < sizeof(Word)) {
            return false;
        }
        push_back(static_cast<uint8_t>(word), address);
        if constexpr (sizeof(Word) == 2) {
            push_back(static_cast<uint8_t>(word >> 8), static_cast<uint16_t>(address + 1));
        }
        return true;
    }

    void pop_front() {
        assert(!empty());
        if (++head_ == Capacity) {
            head_ = 0;
        }
        --count_;
    }

    bool peekEntry(Entry& out) const {
        if (empty()) {
            return false;
        }
        out = entry(0);
        return true;
    }

    void clear() { head_ = count_ = 0; }

    template<class Iterator> void assign(Iterator first, Iterator last, uint16_t address = 0) {
        PrefetchQueue replacement;
        for (; first != last; ++first, ++address) {
            replacement.push_back(*first, address);
        }
        *this = replacement;
    }

    // Byte iteration keeps trace and fixture comparisons independent of the
    // optional fetch-address metadata. Use entry(index) for debugger addresses.
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = uint8_t;
        using difference_type = std::ptrdiff_t;
        using pointer = const uint8_t*;
        using reference = const uint8_t&;

        ConstIterator() = default;
        ConstIterator(const PrefetchQueue* owner, std::size_t offset) : owner_(owner), offset_(offset) {}
        reference operator*() const { return (*owner_)[offset_]; }
        pointer operator->() const { return &**this; }
        ConstIterator& operator++() { ++offset_; return *this; }
        ConstIterator operator++(int) { auto previous = *this; ++*this; return previous; }
        bool operator==(const ConstIterator& other) const { return owner_ == other.owner_ && offset_ == other.offset_; }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }

    private:
        const PrefetchQueue* owner_ = nullptr;
        std::size_t offset_ = 0;
    };

    ConstIterator begin() const { return {this, 0}; }
    ConstIterator end() const { return {this, count_}; }

private:
    std::array<Entry, Capacity> entries_{};
    std::size_t head_ = 0, count_ = 0;

    std::size_t index(std::size_t offset) const {
        const auto position = head_ + offset;
        return position < Capacity ? position : position - Capacity;
    }
};

} // namespace cpu
