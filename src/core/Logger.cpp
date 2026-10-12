#include "Logger.h"

#include <format>

void Logger::reset() {
    cpu_rqgt0_ = false; // Used by 8087 for bus mastering, NYI
    cpu_ready_ = true; // Used for DMA and wait states
    cpu_test_ = false; // Used by 8087 for synchronization, NYI
    cpu_lock_ = false;
    bus_dma_ = 0; // NYI
    dmas_ = 0;
    bus_irq_ = 0xfc; // NYI
    int_ = false;
    bus_iochrdy_ = true; // Used for wait states, NYI
    bus_aen_ = false; // Used for DMA
    bus_tc_ = false; // Used for DMA, NYI
    cga_ = 0;

    // T-Cycle
    t_ = 0;
    // Next T-Cycle
    t_next_ = 0;
    d_ = -1;
    last_s_ = BusStatus::InterruptAcknowledge;
    cpu_status_ = BusStatus::Passive;
    cpu_bus_address_ = 0;
    saved_cpu_address_ = 0;

    beginLogging();
}

void Logger::beginLogging() {
    disassembler_.reset();
    disassembly_.clear();
    disassembly_synced_ = false;
}

void Logger::advance(QueueReadState queueStatus, uint8_t queueByte) {
    bus_ale_ = false;
    if (cpu_status_ != BusStatus::Passive && cpu_status_ != BusStatus::Halt) {
        switch (t_next_) {
            case 0:
            case 4: t_next_ = 1; break;
            case 1: t_next_ = 2; break;
            case 2: t_next_ = 3; break;
            case 3: t_next_ = 5; break;
        }
    } else {
        switch (t_) {
            case 4: d_ = -1; t_next_ = 0; break;
            case 0: t_next_ = 0; break;
            case 1:
            case 2: t_next_ = 6; break;
            case 3:
            case 5: d_ = -1; t_next_ = 4; break;
        }
    }
    if (t_ > 5) {
        t_next_ = 0;
    }
    if (bus_aen_) {
        switch (d_) {
            case -1: d_ = 0; break;
            case 0: d_ = 1; break;
            case 1: d_ = 2; break;
            case 2: d_ = 3; break;
            case 3:
            case 5: d_ = ((bus_iow_ && bus_memr_) || (bus_ior_ && bus_memw_)) ? 4 : 5; break;
            case 4: d_ = -1; break;
        }
    }
    if (d_ < -1 || d_ > 5) {
        t_ = 0;
    }
    if (queueStatus == QueueReadState::Flush) {
        beginLogging();
    } else if (queueStatus == QueueReadState::FirstByte) {
        disassembly_synced_ = true;
    }
    if (disassembly_synced_ &&
        (queueStatus == QueueReadState::FirstByte || queueStatus == QueueReadState::SubsequentByte)) {
        if (!disassembler_.disassemble(queueByte, queueStatus == QueueReadState::FirstByte, disassembly_)) {
            disassembly_.clear();
        }
    }
    last_s_ = cpu_status_;
    t_ = t_next_;
    if (t_ == 4 || d_ == 4) {
        bus_ior_ = false;
        bus_iow_ = false;
        bus_memr_ = false;
        bus_memw_ = false;
    }
}

std::string Logger::getLineData(std::span<const uint8_t> queue, std::size_t queueCapacity,
                            QueueReadState queueStatus, uint8_t queueByte) {
    // Character representing queue status as of last cycle.
    // '.' - No operation
    // 'F' - First byte fetched from queue
    // 'E' - Queue emptied
    // 'S' - Subsequent byte fetched from queue
    static constexpr char qsc[] = ".FES";

    // Character representing HOLD status
    // 'h' - HREQ asserted
    // 'H' - HOLDA asserted
    static constexpr char dmasc[] = " h:H";

    auto hex = [](uint32_t value, int width, bool showPrefix = false) -> std::string
    { return std::format("{}{:0{}X}", showPrefix ? "0x" : "", value, width); };

    std::string line;

    // Emit ALE status
    line += bus_ale_ ? "A:" : "  ";
    if (bus_ale_) {
        bus_ale_ = false;
    }

    // Emit address bus value
    line += hex(bus_address_, 5, false) + ":";
    line += hex(cpu_address_, 5, false) + ":";

    // Emit data bus value when defined
    line += (isa_data_floating_ ? "  " : hex(bus_data_, 2, false)) + ' ';

    // Emit bus status
    switch (cpu_status_) {
        case BusStatus::InterruptAcknowledge:
            line += "INTA";
            break;
        case BusStatus::IoRead:
            line += "IOR ";
            break;
        case BusStatus::IoWrite:
            line += "IOW ";
            break;
        case BusStatus::Halt:
            line += "HALT";
            break;
        case BusStatus::InstructionFetch:
            line += "CODE";
            break;
        case BusStatus::MemoryRead:
            line += "MEMR";
            break;
        case BusStatus::MemoryWrite:
            line += "MEMW";
            break;
        case BusStatus::Passive:
            line += "PASV";
            break;
        default:
            break;
    }

    // Emit QS, RQ/GT, ready line, TEST pin, LOCK pin
    line += " " + std::string(1, qsc[static_cast<int>(queueStatus)]) + (cpu_rqgt0_ ? "G" : ".") +
        (cpu_ready_ ? "." : "z") + (cpu_test_ ? "T" : ".") + (cpu_lock_ ? "L" : ".") + "  ";

    // Emit DMA status
    line += " " + hex(bus_dma_, 2, false) + dmasc[dmas_] + " ";

    // Emit IRQ status
    line += hex(bus_irq_, 2, false) + (int_ ? "I" : " ") + " ";

    // Emit PIT & CGA status.
    line += hex(bus_pit_, 1, false) + " " + hex(cga_, 1, false) + " " + (bus_ior_ ? "R" : ".") +
        (bus_iow_ ? "W" : ".") + (bus_memr_ ? "r" : ".") + (bus_memw_ ? "w" : ".") + (bus_iochrdy_ ? "." : "z") +
        (bus_aen_ ? "D" : ".") + (bus_tc_ ? "T" : ".");

    line += "  ";
    if (cpu_status_ != BusStatus::Passive && cpu_status_ != BusStatus::Halt) {
        switch (t_next_) {
            case 0:
            case 4:
                // T1 state occurs after transition out of passive
                t_next_ = 1;
                break;
            case 1:
                t_next_ = 2;
                break;
            case 2:
                t_next_ = 3;
                break;
            case 3:
                t_next_ = 5;
                break;
        }
    }
    else {
        switch (t_) {
            case 4:
                d_ = -1;
            case 0:
                t_next_ = 0;
                break;
            case 1:
            case 2:
                t_next_ = 6;
                break;
            case 3:
            case 5:
                d_ = -1;
                t_next_ = 4;
                break;
        }
    }
    switch (t_) {
        case 0:
            line += "  ";
            break;
        case 1:
            line += "T1";
            break;
        case 2:
            line += "T2";
            break;
        case 3:
            line += "T3";
            break;
        case 4:
            line += "T4";
            break;
        case 5:
            line += "Tw";
            break;
        default:
            line += "!c";
            t_next_ = 0;
            break;
    }
    line += " ";
    if (bus_aen_) {
        switch (d_) {
            // This is a bit of a hack since we don't have access
            // to the right lines to determine the DMA state
            // properly. This probably breaks for memory-to-memory
            // copies.
            case -1:
                d_ = 0;
                break;
            case 0:
                d_ = 1;
                break;
            case 1:
                d_ = 2;
                break;
            case 2:
                d_ = 3;
                break;
            case 3:
            case 5:
                if ((bus_iow_ && bus_memr_) || (bus_ior_ && bus_memw_)) {
                    d_ = 4;
                }
                else {
                    d_ = 5;
                }
                break;
            case 4:
                d_ = -1;
        }
    }

    // Emit DMA cycle state
    switch (d_) {
        case -1:
            line += "   ";
            break;
        case 0:
            line += "S0 ";
            break;
        case 1:
            line += "S1 ";
            break;
        case 2:
            line += "S2 ";
            break;
        case 3:
            line += "S3 ";
            break;
        case 4:
            line += "S4 ";
            break;
        case 5:
            line += "SW ";
            break;
        default:
            line += "!d ";
            t_ = 0;
            break;
    }

    // Emit the CPU's actual queue contents after this clock's operations.
    line += '[';
    for (std::size_t i = 0; i < queueCapacity; ++i) {
        if (i < queue.size()) {
            line += hex(queue[i], 2, false);
        }
        else {
            line += "  ";
        }
    }
    line += "] ";

    // QS reports the previous clock's read; the CPU retained its byte. If
    // logging began mid-instruction, wait for a first byte before decoding.
    if (queueStatus == QueueReadState::Flush) {
        beginLogging();
    }
    else if (queueStatus == QueueReadState::FirstByte) {
        disassembly_synced_ = true;
    }
    if (disassembly_synced_ &&
        (queueStatus == QueueReadState::FirstByte || queueStatus == QueueReadState::SubsequentByte)) {
        if (!disassembler_.disassemble(queueByte, queueStatus == QueueReadState::FirstByte, disassembly_)) {
            disassembly_ = "";
        }
    }

    // Emit data bus operation
    if (t_next_ == 4 || d_ == 4) {
        if (t_next_ == 4 && d_ == 4) {
            line += "!e";
        }
        std::string seg;
        // Decode segment status from address lines
        switch (cpu_address_ & 0x30000) {
            case 0x00000:
                seg = "ES ";
                break;
            case 0x10000:
                seg = "SS ";
                break;
            case 0x20000:
                seg = "CS ";
                break;
            case 0x30000:
                seg = "DS ";
                break;
            default:
                break;
        }

        std::string type = "-";
        if (last_s_ == BusStatus::InterruptAcknowledge) {
            // Interrupt
            line += hex(bus_data_, 2, false) + " <-i           ";
        }
        else {
            if (last_s_ == BusStatus::InstructionFetch) {
                // Code fetch
                type = "f";
                seg = "   ";
            }
            if (d_ == 4) {
                // DMA transfer on S4
                type = "d";
                seg = "   ";
            }

            line += hex(bus_data_, 2, false) + " ";

            if (bus_ior_ || bus_memr_) {
                // CPU Bus read
                line += "<-" + type + " ";
            }
            else {
                line += type + "-> ";
            }

            if (bus_memr_ || bus_memw_) {
                // Emit bus address of transfer
                line += "[" + seg + hex(bus_address_, 5, false) + "]";
            }
            else {
                // IO operation
                line += "port[" + hex(bus_address_ & 0xffff, 4, false) + "]";
            }

        }
        line += " ";
    }
    else {
        line += "                  ";
    }

    if (queueStatus != QueueReadState::NoOperation) {
        line += std::string(1, qsc[static_cast<int>(queueStatus)]);
    }
    else {
        line += " ";
    }

    // Keep the microcode column fixed, even when disassembly is long.
    line += ' ';
    line.append(disassembly_, 0, kDisassemblyWidth);
    line.resize(kMicrocodeColumn, ' ');
    // Latch last status
    last_s_ = cpu_status_;
    // Advance T-state
    t_ = t_next_;
    // Reset bus signals at T4
    if (t_ == 4 || d_ == 4) {
        bus_ior_ = false;
        bus_iow_ = false;
        bus_memr_ = false;
        bus_memw_ = false;
    }
    return line;
}
