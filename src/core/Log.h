// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <iostream>
#include <streambuf>
#include <utility>

namespace xtce::log {

// Increasing severity. Off disables every level and is never a message level.
enum class Level
{
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Off
};

namespace detail {

class NullBuffer : public std::streambuf
{
protected:
    int_type overflow(int_type ch) override { return traits_type::not_eof(ch); }
    std::streamsize xsputn(const char*, std::streamsize count) override { return count; }
};

struct State {
    std::ostream* output = &std::cout;
    Level minimum_level = Level::Info;
    NullBuffer null_buffer;
    std::ostream null_stream{&null_buffer};
};

inline State& state() {
    static State value;
    return value;
}

} // namespace detail

// check if a log level is enabled.
// Use enabled() before constructing expensive diagnostic data.
inline bool enabled(const Level level) {
    return level != Level::Off && level >= detail::state().minimum_level;
}


inline std::ostream& stream(const Level level) {
    auto& state = detail::state();
    return enabled(level) ? *state.output : state.null_stream;
}

// Log level helpers
inline std::ostream& trace() { return stream(Level::Trace); }
inline std::ostream& debug() { return stream(Level::Debug); }
inline std::ostream& info() { return stream(Level::Info); }
inline std::ostream& warn() { return stream(Level::Warn); }
inline std::ostream& error() { return stream(Level::Error); }

// Set the output log level
inline std::ostream& setOutput(std::ostream& output) {
    return *std::exchange(detail::state().output, &output);
}

// Info is the default: normal events, warnings and errors are visible.
inline Level setMinimumLevel(Level level) {
    return std::exchange(detail::state().minimum_level, level);
}

// Accepts any ostream, including ostringstream for memory and ofstream for files.
class ScopedOutput
{
public:
    explicit ScopedOutput(std::ostream& output) : previous_(setOutput(output)) {}
    ~ScopedOutput() { setOutput(previous_); }
    ScopedOutput(const ScopedOutput&) = delete;
    ScopedOutput& operator=(const ScopedOutput&) = delete;

private:
    std::ostream& previous_;
};

class ScopedLevel
{
public:
    explicit ScopedLevel(Level level) : previous_(setMinimumLevel(level)) {}
    ~ScopedLevel() { setMinimumLevel(previous_); }
    ScopedLevel(const ScopedLevel&) = delete;
    ScopedLevel& operator=(const ScopedLevel&) = delete;

private:
    Level previous_;
};

} // namespace xtce::log
