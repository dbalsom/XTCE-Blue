#pragma once

#include <cstdint>

#include "DebuggerWindow.h"

class Machine;

class VideoCardStatusWindow : public DebuggerWindow
{
public:
    explicit VideoCardStatusWindow(Machine* m) :
        _machine(m) {
    }

    ~VideoCardStatusWindow() override = default;

    void show(bool* open) override;

    [[nodiscard]] const char* name() const override { return "Video Card Status"; }

private:
    Machine* _machine{nullptr};
    uint64_t _prev_frame_count{0};
    uint64_t _prev_ticks{0};
    double _instant_refresh_hz{0.0};
};
