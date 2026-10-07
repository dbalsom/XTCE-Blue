#pragma once

#include <cmath>
#include <cstdint>

class EmulationClock
{
public:
    EmulationClock(const double cpu_hz, const uint64_t counter_frequency, const double max_catchup_seconds = 0.05) :
        cpu_hz_(cpu_hz), counter_frequency_(counter_frequency),
        max_catchup_cycles_(static_cast<uint64_t>(cpu_hz * max_catchup_seconds)) {}

    void reset(const uint64_t counter, const uint64_t cycles, const bool running) {
        epoch_counter_ = last_counter_ = counter;
        epoch_cycles_ = last_cycles_ = cycles;
        running_ = running;
    }

    uint64_t cyclesDue(const uint64_t counter, const uint64_t cycles, const bool running) {
        if (!running || !running_ || counter < last_counter_ || cycles < last_cycles_) {
            // Time spent paused, or before a reset, does not become CPU work.
            reset(counter, cycles, running);
            return 0;
        }
        last_counter_ = counter;
        last_cycles_ = cycles;

        // Round only the absolute target. Fractional cycles survive every host
        // iteration, including iterations shorter than one emulated CPU cycle.
        const auto elapsed = static_cast<long double>(counter - epoch_counter_) / counter_frequency_;
        const uint64_t target = epoch_cycles_ + static_cast<uint64_t>(std::floor(elapsed * cpu_hz_));
        if (target <= cycles) {
            return 0;
        }

        const uint64_t due = target - cycles;
        if (due > max_catchup_cycles_) {
            // Rebase after a long stall instead of carrying an endless backlog.
            epoch_counter_ = counter;
            epoch_cycles_ = cycles + max_catchup_cycles_;
            return max_catchup_cycles_;
        }
        return due;
    }

private:
    double cpu_hz_;
    uint64_t counter_frequency_;
    uint64_t max_catchup_cycles_;
    uint64_t epoch_counter_{0};
    uint64_t epoch_cycles_{0};
    uint64_t last_counter_{0};
    uint64_t last_cycles_{0};
    bool running_{false};
};
