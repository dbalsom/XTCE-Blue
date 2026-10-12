#pragma once

#include <array>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

#include "Disassembler.h"
#include "cpu_types.h"

class Logger
{
public:
    static constexpr std::size_t kDisassemblyColumn = 88;
    static constexpr std::size_t kDisassemblyWidth = 48;
    static constexpr std::size_t kMicrocodeColumn = kDisassemblyColumn + kDisassemblyWidth;

    void reset();
    void beginLogging();
    void advance(QueueReadState queueStatus, uint8_t queueByte);

    template<class Queue>
    std::string getLine(const Queue& queue, QueueReadState queueStatus, uint8_t queueByte,
                        std::size_t visibleCapacity = Queue::capacity) {
        std::array<uint8_t, Queue::capacity> bytes{};
        const std::size_t size = std::min(queue.size(), visibleCapacity);
        for (std::size_t i = 0; i < size; ++i) {
            bytes[i] = queue[i];
        }
        return getLineData(std::span<const uint8_t>(bytes.data(), size), visibleCapacity,
                           queueStatus, queueByte);
    }

    void setStatus(const BusStatus bus_status) {
        cpu_last_status_ = cpu_status_;
        cpu_status_ = bus_status;
        // Bus proceeding from PASV to any other status triggers ALE signal.
        if (cpu_last_status_ == BusStatus::Passive && cpu_status_ != BusStatus::Passive) {
            bus_ale_ = true;
        }
        else {
            bus_ale_ = false;
        }
    }

    void setStatusHigh(const int segment) {
        cpu_address_ &= 0xcffff;
        switch (segment) {
            case 0: // ES
                break;
            case 2: // SS
                cpu_address_ |= 0x10000;
                break;
            case 3: // DS
                cpu_address_ |= 0x30000;
                break;
            default: // CS or none
                cpu_address_ |= 0x20000;
                break;
        }
        setBusFloating();
    }

    void setInterruptFlag(bool intf) { cpu_address_ = (cpu_address_ & 0xbffff) | (intf ? 0x40000 : 0); }

    void setBusOperation(BusStatus bus_status) {
        switch (bus_status) {
            case BusStatus::IoRead:
                bus_ior_ = true;
                break;
            case BusStatus::IoWrite:
                bus_iow_ = true;
                break;
            case BusStatus::InstructionFetch:
            case BusStatus::MemoryRead:
                bus_memr_ = true;
                break;
            case BusStatus::MemoryWrite:
                bus_memw_ = true;
                break;
            default:
                break;
        }
    }

    void setData(const uint8_t data) {
        cpu_address_ = (cpu_address_ & 0xfff00) | data;
        bus_data_ = data;
        cpu_data_floating_ = false;
        isa_data_floating_ = false;
    }

    void setCpuAddress(const uint32_t address) {
        cpu_bus_address_ = address & 0xfffff;
        setAddress(cpu_bus_address_);
    }

    void setDmaAddress(const uint32_t address) {
        saved_cpu_address_ = cpu_bus_address_;
        setAddress(address);
    }

    void restoreCpuAddress() { setAddress(saved_cpu_address_); }

    uint32_t getAddress() const { return cpu_address_; }

    void setBusFloating() {
        cpu_data_floating_ = true;
        isa_data_floating_ = true;
    }

    void setPITBits(int bits) { bus_pit_ = bits; }
    void setAEN(bool aen) { bus_aen_ = aen; }
    void setDMA(uint8_t dma) { bus_dma_ = dma; }
    void setReady(bool ready) { cpu_ready_ = ready; }
    void setLock(bool lock) { cpu_lock_ = lock; }
    void setDMAS(uint8_t dmas) { dmas_ = dmas; }
    void setIRQs(uint8_t irq) { bus_irq_ = irq; }
    void setINT(bool intrq) { int_ = intrq; }
    void setCGA(uint8_t cga) { cga_ = cga; }

private:
    void setAddress(const uint32_t address) {
        cpu_address_ = address & 0xfffff;
        bus_address_ = address & 0xfffff;
        cpu_data_floating_ = false;
    }

    std::string getLineData(std::span<const uint8_t> queue, std::size_t queueCapacity,
                            QueueReadState queueStatus, uint8_t queueByte);

    Disassembler disassembler_;
    std::string disassembly_;
    bool disassembly_synced_{false};

    // Internal variables that we use to keep track of what's going on in order
    // to be able to print useful logs.

    // 0 = TIdle, 1 = T1, 2 = T2, 3 = T3, 4 = T4, 5 = TWait
    int t_{0};
    int t_next_{0};

    // -1 = SI, 0 = S0, 1 = S1, 2 = S2, 3 = S3, 4 = S4, 5 = SW
    int d_{-1};
    BusStatus last_s_{BusStatus::InterruptAcknowledge};

    // CPU address latched at T1, before the address pins carry status or data.
    uint32_t cpu_bus_address_ = 0;

    // CPU address to restore after the logger temporarily displays a DMA address.
    uint32_t saved_cpu_address_ = 0;

    // CPU and ISA bus pins used to create the cycle logs.

    // A19/S6, A18/S5, A17/S4, A16/S3 (output) ADDRESS/STATUS:
    // During T1, these are the four most significant address lines for memory operations. During I/O operations,
    // these lines are LOW. During memory and I/O operations, status information is available on these lines during
    // T2, T3, Tw, and T4. S6 is always low. The interrupt enable flag bit (S5) is updated at the beginning of each
    // clock cycle. S4*2+S3: 0 = Alternate Data, 1 = Stack, 2 = Code or None, 3 = Data.
    //
    // A15..A8 (output) ADDRESS BUS:
    // These lines provide address bits 8 through 15 for the entire bus cycle (T1-T4). They do not have to be latched
    // by ALE to remain valid. They are active HIGH and float to 3-state OFF during interrupt acknowledge and local
    // bus "hold acknowledge".
    //
    // AD7..AD0 (I/O) ADDRESS DATA BUS:
    // These lines constitute the time-multiplexed memory/I/O address (T1) and data (T2, T3, Tw, T4) bus. They are
    // active HIGH and float to 3-state OFF during interrupt acknowledge and local bus "hold acknowledge".
    uint32_t cpu_address_ = 0;

    // -S2..-S0 (output) STATUS:
    // Active during clock high of T4, T1, and T2; returned to the passive state (1,1,1) during T3 or during Tw when
    // READY is HIGH. The 8288 bus controller uses this status to generate all memory and I/O access control signals.
    // Any change by S2, S1, or S0 during T4 indicates the beginning of a bus cycle; the return to the passive state
    // in T3 and Tw indicates the end. These signals float to 3-state OFF during "hold acknowledge". During the first
    // clock cycle after RESET becomes active, they are active HIGH. After this first clock, they float to 3-state OFF.
    // 0 = Interrupt Acknowledge, 1 = Read I/O Port, 2 = Write I/O Port, 3 = Halt, 4 = Code Access,
    // 5 = Read Memory, 6 = Write Memory, 7 = Passive.
    BusStatus cpu_status_ = BusStatus::Passive;

    // The last CPU status. We can derive ALE from the change from Passive to any other status.
    BusStatus cpu_last_status_ = BusStatus::Passive;

    // -RQ/-GT0 (!87, I/O) REQUEST/GRANT:
    // Used by other local bus masters to force the processor to release the local bus at the end of its current bus
    // cycle. Each pin is bidirectional, with RQ/GT0 having higher priority than RQ/GT1. RQ/GT has an internal pull-up
    // resistor, so may be left unconnected.
    bool cpu_rqgt0_{false};

    // READY (input):
    // Acknowledgement from the addressed memory or I/O device that it will complete the data transfer. The RDY
    // signal from memory or I/O is synchronized by the 8284 clock generator to form READY. This signal is active
    // HIGH. The 8088 READY input is not synchronized. Correct operation is not guaranteed if the setup and hold
    // times are not met.
    bool cpu_ready_{false};

    // -TEST (input):
    // Examined by the "wait for test" instruction. If the TEST input is LOW, execution continues; otherwise, the
    // processor waits in an "idle" state. This input is synchronized internally during each clock cycle on the
    // leading edge of CLK.
    bool cpu_test_{false};

    // -LOCK (!87, output):
    // Indicates that other system bus masters are not to gain control of the system bus while LOCK is active (LOW).
    // Activated by the "LOCK" prefix instruction and remains active until the completion of the next instruction.
    // This signal is active LOW and floats to 3-state OFF during "hold acknowledge".
    bool cpu_lock_{false};

    // +A19..+A0 (output) Address bits:
    // Used to address memory and I/O devices within the system. Generated by either the processor or DMA controller.
    uint32_t bus_address_{0};

    // +D7..+D0 (I/O) Data bits:
    // Provide data bus bits 0 to 7 for the processor, memory, and I/O devices.
    uint8_t bus_data_{0};

    // +DRQ0 JP6/1 == U28.19 == U73.9
    // +DRQ1..+DRQ3 (input) DMA Request:
    // Asynchronous channel requests used by peripheral devices to gain DMA service. Prioritized with DRQ3 being the
    // lowest and DRQ1 being the highest. A request is generated by bringing a DRQ line to an active level (high).
    // A DRQ line must be held high until the corresponding DACK line goes active.
    //
    // -DACK0..-DACK3 (output) DMA Acknowledge:
    // Used to acknowledge DMA requests (DRQ1-DRQ3) and to refresh system dynamic memory (DACK0). Active low.
    uint8_t bus_dma_{0};

    // JP9/4 HRQ DMA (bit 0), JP4/1 HOLDA (bit 1)
    uint8_t dmas_{0};

    // +IRQ0..+IRQ7 (input) Interrupt Request:
    // Signal the processor that an I/O device requires attention. A request is generated by raising an IRQ line
    // (low to high) and holding it high until it is acknowledged by the processor (interrupt service routine).
    uint8_t bus_irq_{0};

    // JP9/1 INT
    bool int_{false};

    // JP7/2 CGA HCLK (bit 0), JP7/1 CGA LCLK (bit 1)
    uint8_t cga_{0};

    // Clock, gate, output
    uint8_t bus_pit_{0};

    // ALE: Address Latch Enable
    bool bus_ale_{false};

    // -IOR (output) I/O Read Command:
    // Instructs an I/O device to drive its data onto the data bus. May be driven by the processor or DMA controller.
    // This signal is active low.
    bool bus_ior_{true};

    // -IOW (output) I/O Write Command:
    // Instructs an I/O device to read the data on the data bus. May be driven by the processor or DMA controller.
    // This signal is active low.
    bool bus_iow_{true};

    // -MEMR (output) Memory Read Command:
    // Instructs the memory to drive its data onto the data bus. May be driven by the processor or DMA controller.
    // This signal is active low.
    bool bus_memr_{true};

    // -MEMW (output) Memory Write Command:
    // Instructs the memory to store the data present on the data bus. May be driven by the processor or DMA controller.
    // This signal is active low.
    bool bus_memw_{true};

    // +I/O CH RDY (input) I/O Channel Ready:
    // Normally high (ready); pulled low (not ready) by a memory or I/O device to lengthen I/O or memory cycles. Allows
    // slower devices to attach to the I/O channel with a minimum of difficulty. Any slow device using this line
    // should drive it low immediately upon detecting a valid address and a read or write command. This line should
    // never be held low longer than 10 clock cycles. Machine cycles (I/O or memory) are extended by an integral
    // number of CLK cycles (210 ns).
    bool bus_iochrdy_{false};

    // +AEN (output) Address Enable:
    // De-gates the processor and other devices from the I/O channel to allow DMA transfers. When active (high), the
    // DMA controller has control of the address bus, data bus, read command lines (memory and I/O), and write command
    // lines (memory and I/O).
    bool bus_aen_{false};

    // +T/C (output) Terminal Count:
    // Provides a pulse when the terminal count for any DMA channel is reached. This signal is active high.
    bool bus_tc_{false};

    bool cpu_data_floating_{false};
    bool isa_data_floating_{false};
};
