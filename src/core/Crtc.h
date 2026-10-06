#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

class Crtc6845
{
public:
    // --- Public types and constants -------------------------------------------------------------

    enum class CursorStatus : uint8_t
    {
        Solid,
        Hidden,
        Blink,
        SlowBlink,
    };

    enum class CrtcRegister : uint8_t
    {
        HorizontalTotal = 0,
        HorizontalDisplayed,
        HorizontalSyncPosition,
        SyncWidth,
        VerticalTotal,
        VerticalTotalAdjust,
        VerticalDisplayed,
        VerticalSync,
        InterlaceMode,
        MaximumScanlineAddress,
        CursorStartLine,
        CursorEndLine,
        StartAddressH,
        StartAddressL,
        CursorAddressH,
        CursorAddressL,
        LightPenPositionH,
        LightPenPositionL,
        InvalidRegister,
    };

    struct CrtcStatusBits
    {
        bool hblank = false;
        bool vblank = false;
        bool den = false; // Display Enable within active area
        bool hborder = false;
        bool vborder = false;
        bool cursor = false;
        bool hsync = false; // CRTC HSYNC level (also exposed as hblank)
        bool vsync = false; // CRTC VSYNC level (also exposed as vblank)
    };

    static constexpr uint8_t CURSOR_LINE_MASK = 0b0001'1111;
    static constexpr uint8_t CURSOR_ATTR_MASK = 0b0110'0000;

    static constexpr uint8_t BLINK_FAST_RATE = 8;
    static constexpr uint8_t BLINK_SLOW_RATE = 16;

    static constexpr uint8_t CRTC_VBLANK_HEIGHT = 16;
    static constexpr size_t REGISTER_MAX = 17;
    static constexpr uint8_t REGISTER_UNREADABLE_VALUE = 0xFF;

public:
    explicit Crtc6845();

    void reset() {
        reg_ = {}; // externally accessible CRTC register file
        reg_select_ = CrtcRegister::HorizontalTotal;

        start_address_ = 0;
        start_address_latch_ = 0;
        lightpen_position_ = 0;

        cursor_address_ = 0;
        cursor_enabled_ = false;
        cursor_start_line_ = 0;
        cursor_active_ = false;
        blink_state_ = false;
        frames_ = 0;
        has_cursor_blink_rate_ = true;
        cursor_blink_rate_ = BLINK_FAST_RATE;

        hcc_c0_ = 0;
        vlc_c9_ = 0;
        vcc_c4_ = 0;
        vsc_c3h_ = 0;
        hsc_c3l_ = 0;
        vtac_c5_ = 0;
        in_vta_ = false;
        last_line_ = false;
        last_row_ = false;
        previous_last_line_ = false;
        vma_ = 0;
        vma_t_ = 0;
        in_hsync_ = false;
        in_vsync_ = false;
        horizontal_de_ = false;
        vertical_de_ = false;
        status_ = {};
        in_last_vblank_line_ = false;
    }

    void write(uint16_t rel_port, uint8_t data);
    [[nodiscard]] uint8_t read(uint16_t rel_port) const;

    // Step one character time. Returns (status_ptr, current_vma).
    std::pair<const CrtcStatusBits*, uint16_t> tick();
    void latch_lightpen();

    [[nodiscard]] uint16_t start_address() const { return start_address_latch_; }
    [[nodiscard]] uint16_t address() const { return vma_; }
    [[nodiscard]] uint8_t vlc() const { return vlc_c9_; } // vertical line counter (scanline within char row)
    [[nodiscard]] uint8_t hcc() const { return hcc_c0_; }
    [[nodiscard]] uint8_t vcc() const { return vcc_c4_; }
    [[nodiscard]] uint8_t hsc() const { return hsc_c3l_; }
    [[nodiscard]] uint8_t vsc() const { return vsc_c3h_; }
    [[nodiscard]] uint8_t vtac() const { return vtac_c5_; }
    [[nodiscard]] bool last_row() const { return last_row_; }
    [[nodiscard]] bool last_line() const { return last_line_; }
    [[nodiscard]] bool in_vta() const { return in_vta_; }
    [[nodiscard]] const CrtcStatusBits& status() const { return status_; }
    [[nodiscard]] bool hblank() const { return in_hsync_; }
    [[nodiscard]] bool vblank() const { return in_vsync_; }
    [[nodiscard]] bool vsync() const { return in_vsync_; }
    [[nodiscard]] bool hsync() const { return in_hsync_; }
    [[nodiscard]] bool den() const { return horizontal_de_ && vertical_de_; }
    [[nodiscard]] bool border() const { return !horizontal_de_ || !vertical_de_; }

    [[nodiscard]] uint16_t cursor_address() const { return cursor_address_; }
    [[nodiscard]] std::pair<uint8_t, uint8_t> cursor_extents() const { return {cursor_start_line_, reg_[11]}; }
    [[nodiscard]] bool cursor_immediate() const; // current cursor output (includes blink gating)
    [[nodiscard]] bool cursor_enabled() const { return cursor_enabled_; }

    [[nodiscard]] const std::array<uint8_t, 18>& get_registers() const { return reg_; }

private:
    void select_register(uint8_t idx);
    void write_register(uint8_t byte);
    [[nodiscard]] uint8_t read_register() const;

    void update_start_address();
    void update_cursor_address();
    void process_last_line();
    void process_start_of_frame();
    void update_status();

    static void trace_regs_() {}

    std::array<uint8_t, 18> reg_{}; // externally accessible CRTC register file
    CrtcRegister reg_select_ = CrtcRegister::HorizontalTotal;

    uint16_t start_address_ = 0; // from R12/R13
    uint16_t start_address_latch_ = 0; // latched per frame
    uint16_t lightpen_position_ = 0; // from R16/R17 (read-only)

    uint16_t cursor_address_ = 0; // from R14/R15
    bool cursor_enabled_ = false;
    uint8_t cursor_start_line_ = 0;
    bool cursor_active_ = false;
    bool blink_state_ = false;
    uint64_t frames_ = 0;
    bool has_cursor_blink_rate_ = true;
    uint8_t cursor_blink_rate_ = BLINK_FAST_RATE;

    // --- CRTC counters ------------------------------------------------------------------------
    uint8_t hcc_c0_ = 0; // Horizontal character counter
    uint8_t vlc_c9_ = 0; // Vertical line counter within character row
    uint8_t vcc_c4_ = 0; // C4 vertical character counter
    uint8_t vsc_c3h_ = 0; // C3H counts completed HSYNC pulses during VSYNC
    uint8_t hsc_c3l_ = 0; // Four-bit horizontal sync down-counter
    uint8_t vtac_c5_ = 0; // C5 increments before comparing > R5; can reach 32
    bool in_vta_ = false;
    bool last_line_ = false;
    bool last_row_ = false;
    bool previous_last_line_ = false; // Sampled at the end of the CRTC's horizontal sync.
    uint16_t vma_ = 0; // current video memory address
    uint16_t vma_t_ = 0; // temporary holding VMA' for next row start

    bool in_hsync_ = false;
    bool in_vsync_ = false;
    bool horizontal_de_ = false;
    bool vertical_de_ = false;

    CrtcStatusBits status_{};
    bool in_last_vblank_line_ = false;
};
