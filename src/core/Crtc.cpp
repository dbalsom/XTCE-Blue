// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#include "Crtc.h"

Crtc6845::Crtc6845() { reset(); }

// Write to a CRTC register.
// rel_port: 0 = address/select, 1 = data
void Crtc6845::write(const uint16_t rel_port, const uint8_t data) {
    switch (rel_port & 0x01) {
        case 0:
            // address / register select
            select_register(data);
            break;
        case 1:
            // register data write
            write_register(data);
            break;
        default:
            break;
    }
}

// Read from a CRTC register.
uint8_t Crtc6845::read(const uint16_t rel_port) const {
    switch (rel_port & 0x01) {
        case 0:
            // address register not readable
            return 0xFF;
        case 1:
            // data register (partially readable)
            return read_register();
        default:
            return 0xFF;
    }
}

void Crtc6845::select_register(const uint8_t idx) {
    if (idx > REGISTER_MAX) {
        reg_select_ = CrtcRegister::InvalidRegister;
        return;
    }
    switch (idx) {
        case 0:
            reg_select_ = CrtcRegister::HorizontalTotal;
            break;
        case 1:
            reg_select_ = CrtcRegister::HorizontalDisplayed;
            break;
        case 2:
            reg_select_ = CrtcRegister::HorizontalSyncPosition;
            break;
        case 3:
            reg_select_ = CrtcRegister::SyncWidth;
            break;
        case 4:
            reg_select_ = CrtcRegister::VerticalTotal;
            break;
        case 5:
            reg_select_ = CrtcRegister::VerticalTotalAdjust;
            break;
        case 6:
            reg_select_ = CrtcRegister::VerticalDisplayed;
            break;
        case 7:
            reg_select_ = CrtcRegister::VerticalSync;
            break;
        case 8:
            reg_select_ = CrtcRegister::InterlaceMode;
            break;
        case 9:
            reg_select_ = CrtcRegister::MaximumScanlineAddress;
            break;
        case 10:
            reg_select_ = CrtcRegister::CursorStartLine;
            break;
        case 11:
            reg_select_ = CrtcRegister::CursorEndLine;
            break;
        case 12:
            reg_select_ = CrtcRegister::StartAddressH;
            break;
        case 13:
            reg_select_ = CrtcRegister::StartAddressL;
            break;
        case 14:
            reg_select_ = CrtcRegister::CursorAddressH;
            break;
        case 15:
            reg_select_ = CrtcRegister::CursorAddressL;
            break;
        case 16:
            reg_select_ = CrtcRegister::LightPenPositionH;
            break;
        default:
            reg_select_ = CrtcRegister::LightPenPositionL;
            break;
    }
}

void Crtc6845::write_register(const uint8_t byte) {
    switch (reg_select_) {
        case CrtcRegister::HorizontalTotal:
            // R0: 8-bit
            reg_[0] = byte;
            break;

        case CrtcRegister::HorizontalDisplayed:
            // R1: 8-bit
            reg_[1] = byte;
            break;

        case CrtcRegister::HorizontalSyncPosition:
            // R2: 8-bit
            reg_[2] = byte;
            break;

        case CrtcRegister::SyncWidth:
            // R3: 8-bit
            reg_[3] = byte;
            break;

        case CrtcRegister::VerticalTotal:
            // R4: 7-bit
            reg_[4] = static_cast<uint8_t>(byte & 0x7F);
            // std::cout << "CRTC Register Write (04h): VerticalTotal updated: " << static_cast<unsigned>(reg_[4]);
            break;

        case CrtcRegister::VerticalTotalAdjust:
            // R5: 5-bit
            reg_[5] = static_cast<uint8_t>(byte & 0x1F);
            break;

        case CrtcRegister::VerticalDisplayed:
            // R6: 7-bit
            reg_[6] = static_cast<uint8_t>(byte & 0x7F);
            break;

        case CrtcRegister::VerticalSync:
            // R7: 7-bit
            reg_[7] = static_cast<uint8_t>(byte & 0x7F);
            trace_regs_();
            // std::cout <<  "CRTC Register Write (07h): VerticalSync updated: " << static_cast<unsigned>(reg_[7]);
            break;

        case CrtcRegister::InterlaceMode:
            // R8: 2-bit
            reg_[8] = static_cast<uint8_t>(byte & 0x03);
            break;

        case CrtcRegister::MaximumScanlineAddress:
            // R9: 5-bit
            reg_[9] = static_cast<uint8_t>(byte & 0x1F);
            break;

        case CrtcRegister::CursorStartLine:
            {
                // R10: 7-bit field; includes cursor attrs in upper nibble
                reg_[10] = static_cast<uint8_t>(byte & 0x7F);

                cursor_start_line_ = static_cast<uint8_t>(byte & CURSOR_LINE_MASK);

                // IMPORTANT: parentheses — we want (byte & mask) >> 4
                const uint8_t attr = static_cast<uint8_t>((byte & CURSOR_ATTR_MASK) >> 5);
                switch (attr) {
                    case 0b00:
                        cursor_enabled_ = true;
                        has_cursor_blink_rate_ = false; // solid
                        break;
                    case 0b01:
                        cursor_enabled_ = false; // disabled (some hardware still blinks visually, but we gate here)
                        has_cursor_blink_rate_ = false;
                        break;
                    case 0b10:
                        cursor_enabled_ = true;
                        has_cursor_blink_rate_ = true;
                        cursor_blink_rate_ = BLINK_FAST_RATE;
                        break;
                    default:
                        cursor_enabled_ = true;
                        has_cursor_blink_rate_ = true;
                        cursor_blink_rate_ = BLINK_SLOW_RATE;
                        break;
                }
                break;
            }

        case CrtcRegister::CursorEndLine:
            // R11: 5-bit
            reg_[11] = static_cast<uint8_t>(byte & CURSOR_LINE_MASK);
            break;

        case CrtcRegister::StartAddressH:
            // R12: 6-bit
            reg_[12] = static_cast<uint8_t>(byte & 0x3F);
            // std::cout << "CRTC Register Write (0Ch): StartAddressH updated: " << std::hex << std::uppercase <<
            // static_cast<unsigned>(byte);
            update_start_address();
            break;

        case CrtcRegister::StartAddressL:
            // R13: 8-bit
            reg_[13] = byte;
            // std::cout << "CRTC Register Write (0Dh): StartAddressL updated: " << std::hex << std::uppercase <<
            // static_cast<unsigned>(byte);
            update_start_address();
            break;

        case CrtcRegister::CursorAddressH:
            // R14: 6-bit, readable
            reg_[14] = static_cast<uint8_t>(byte & 0x3F);
            update_cursor_address();
            break;

        case CrtcRegister::CursorAddressL:
            // R15: 8-bit, readable
            reg_[15] = byte;
            update_cursor_address();
            break;

        case CrtcRegister::LightPenPositionH:
        case CrtcRegister::LightPenPositionL:
        case CrtcRegister::InvalidRegister:
            // R16: read-only
            // R17: read-only
            break;
    }
}

uint8_t Crtc6845::read_register() const {
    switch (reg_select_) {
        case CrtcRegister::CursorAddressH:
        case CrtcRegister::CursorAddressL:
        case CrtcRegister::LightPenPositionH:
        case CrtcRegister::LightPenPositionL:
            return reg_[static_cast<size_t>(reg_select_)];
        default:
            return REGISTER_UNREADABLE_VALUE;
    }
}

void Crtc6845::update_start_address() {
    start_address_ = static_cast<uint16_t>((static_cast<uint16_t>(reg_[12]) << 8) | reg_[13]);
}

void Crtc6845::update_cursor_address() {
    cursor_address_ = static_cast<uint16_t>((static_cast<uint16_t>(reg_[14]) << 8) | reg_[15]);
}

void Crtc6845::latch_lightpen() {
    lightpen_position_ = vma_;
    reg_[16] = static_cast<uint8_t>((lightpen_position_ >> 8) & 0x3F);
    reg_[17] = static_cast<uint8_t>(lightpen_position_);
}

// Return the immediate status of the cursor
bool Crtc6845::cursor_immediate() const {
    bool cur = cursor_enabled_ && (vma_ == cursor_address_) && cursor_active_;

    if (has_cursor_blink_rate_) {
        cur = cur && blink_state_;
    }
    return cur;
}

// Tick the CRTC
// Returns (status_ptr, current_vma)
std::pair<const Crtc6845::CrtcStatusBits*, uint16_t> Crtc6845::tick() {
    // Sample equality before advancing counters, including R0=255 and R9=31.
    const bool end_of_line = hcc_c0_ == reg_[0];
    const bool end_of_character_row = vlc_c9_ == reg_[9];
    const bool at_vertical_total = vcc_c4_ == reg_[4];

    if (hcc_c0_ == 0) {
        if (vlc_c9_ == cursor_start_line_ && !in_vta_) {
            cursor_active_ = true;
        }
        if (vcc_c4_ == 0 && vlc_c9_ == 0) {
            // We are at the first character of a CRTC frame. Update start address.
            vma_ = start_address_latch_;
        }
        // Latch last-line status only at C0=0. Later register writes must not
        // reevaluate it until the next scanline.
        if (at_vertical_total) {
            last_row_ = true;
            last_line_ = end_of_character_row && !previous_last_line_ && !in_hsync_;
            vtac_c5_ = 0;
        }
        else {
            last_line_ = false;
        }
    }

    // Update horizontal character counter
    hcc_c0_++;
    if (hcc_c0_ == 0) {
        horizontal_de_ = true;
        if (vcc_c4_ == 0) {
            vma_ = start_address_latch_;
        }
    }

    // Advance video memory address offset
    vma_++;

    // Process horizontal blanking period
    if (in_hsync_) {
        // Four-bit down-counter: loading zero gives a 16-character pulse.
        hsc_c3l_ = (hsc_c3l_ - 1) & 0x0F;

        if (hsc_c3l_ == 0) {
            previous_last_line_ = at_vertical_total && end_of_character_row;
            if (in_vsync_) {
                // C3H advances at the end of CRTC HSYNC, independently of C0/R0.
                ++vsc_c3h_;
                if (vsc_c3h_ == CRTC_VBLANK_HEIGHT) {
                    in_last_vblank_line_ = true;
                    vsc_c3h_ = 0;
                    in_vsync_ = false;
                }
            }
            in_hsync_ = false;
        }
    }

    if (hcc_c0_ == reg_[1]) {
        // C0 == R1. Entering right overscan.
        if (end_of_character_row) {
            // Last scanline of this character row; save VMA' for next row
            vma_t_ = vma_;
        }
        horizontal_de_ = false;
    }

    if (hcc_c0_ == reg_[2]) {
        // Load the four-bit C3L down-counter at C0 == R2.
        hsc_c3l_ = reg_[3] & 0x0F;
        in_hsync_ = true;
    }

    if (end_of_line) {
        // C0 == R0: end of scanline.
        if (vlc_c9_ == reg_[11] && !in_vta_) {
            cursor_active_ = false;
        }

        if (in_last_vblank_line_) {
            // Leave VBLANK after last line.
            in_last_vblank_line_ = false;
            in_vsync_ = false;
        }

        // Reset C0. Horizontal DE is independent of the vertical DE latch.
        hcc_c0_ = 0;
        horizontal_de_ = true;

        // Return video memory address to starting position for next character row
        vma_ = vma_t_;

        if (end_of_character_row) {
            // C9 == R9 We finished drawing this row of characters
            vlc_c9_ = 0;
            // C4 must reach 128 after R4=127. Frame management resets it;
            // masking to seven bits here makes the following comparisons wrong.
            ++vcc_c4_;
            // Set vma to starting position for next character row
            vma_ = vma_t_;

            if (vcc_c4_ == reg_[7]) {
                // C4 == R7: We've reached vertical sync
                in_vsync_ = true;

                if (has_cursor_blink_rate_) {
                    if (frames_ % cursor_blink_rate_ == 0) {
                        blink_state_ = !blink_state_;
                    }
                }
            }

            if (last_line_) {
                process_last_line();
            }
        }
        else {
            // Wrap only after testing the current five-bit scanline counter.
            vlc_c9_ = (vlc_c9_ + 1) & 0x1F;
            if (vlc_c9_ == cursor_start_line_ && !in_vta_) {
                cursor_active_ = true;
            }
        }

        if (vcc_c4_ == reg_[6]) {
            // C4 == R6: Enter lower overscan area.
            vertical_de_ = false;
        }

        if (in_vta_) {
            // Match MartyPC's increment-before-comparison order. C5 can reach 32
            // when R5=31; lowering R5 ends adjust on the next scanline.
            ++vtac_c5_;
            if (vtac_c5_ > reg_[5]) {
                process_start_of_frame();
            }
        }
    }

    update_status();
    return {&status_, vma_};
}

void Crtc6845::process_last_line() {
    if (in_vta_) {
        return;
    }
    if (reg_[5] != 0) {
        in_vta_ = true;
        last_row_ = false;
        last_line_ = false;
    }
    else {
        process_start_of_frame();
    }
}

void Crtc6845::process_start_of_frame() {
    ++frames_;
    in_vta_ = false;
    last_row_ = false;
    last_line_ = false;
    vtac_c5_ = 0;
    vcc_c4_ = 0;
    vlc_c9_ = 0;
    start_address_latch_ = start_address_;
    vma_ = start_address_;
    vma_t_ = vma_;
    horizontal_de_ = true;
    vertical_de_ = true;
    in_vsync_ = false;
    // C3H is deliberately retained, as in MartyPC.
}

void Crtc6845::update_status() {
    status_.cursor = cursor_immediate();
    status_.den = den();
    status_.hblank = status_.hsync = in_hsync_;
    status_.vblank = status_.vsync = in_vsync_;
    status_.hborder = !horizontal_de_;
    status_.vborder = !vertical_de_;
}
