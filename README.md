# XTCE-Blue

XTCE-Blue is a cycle-accurate IBM PC emulator with microcode-based, cycle-exact emulation of the Intel 8088 and NEC V20 CPUs.

It started as a fork of [reenigne's XTCE 8088 CPU emulation core](https://github.com/reenigne/reenigne/tree/master/8088/xtce)
providing video emulation, an SDL3 interface and an ImGui-based debugger. Several bugs within XTCE were also fixed.

It eventually incorporated [my own microcode disassembly](https://github.com/dbalsom/x86_microcode) of the NEC V20 and V30 microcode and research into bus timings.

XTCE-Blue integrates several device implementations ported from [MartyPC](https://github.com/dbalsom/martypc), including its precise, overscan-aware CGA emulation.

XTCE-Blue is the only other PC emulator besides MartyPC that can run the final 'lake' effect in the demo [Area 5150](https://www.pouet.net/prod.php?which=91938).

![8088mph_01](/images/8088mph_01.png)
![area5150_01](/images/lake_effect_01.png)

## V20/V30 support

XTCE-Blue now has microcode-based V20 and V30 emulation, the results of the [successful decoding of the NEC V20 microcode](https://martypc.blogspot.com/2026/09/decoding-nec-v20-microcode.html).

8080 emulation mode is supported and has been validated with `8080EXER.COM` against a real V20 CPU.

## Goals
 - Create a clean, well-commented C++ reference emulator for cycle-accurate emulation of the IBM PC/XT.
 - Demonstrate a modern debugging GUI with ImGui for a PC emulator
 - Run 8088 MPH and Area 5150!

## Non-Goals

 - Be a long-term project
   - I don't intend to give up development of my flagship emulator, [MartyPC](https://github.com/dbalsom/martypc). 
     MartyPC has over three years of blood sweat and tears poured into it, and I will continue to improve it into the future.
   - Once XTCE-Blue has proven accurate enough to run the ultimate gauntlet of Area 5150, development on it will likely stop. 
     - You are encouraged to submit PRs to improve the emulator's accuracy, but issues lacking a PR will unlikely be addressed.
     - You are strongly encouraged to fork the entire project to make the emulator of your dreams!

## Debugger Features

 - CPU status display with registers, flags, prefetch queue contents, microcode state and more
   - Stepping by CPU cycle or by instruction boundaries (a bit glitchy still).
   - Single code execution breakpoint (CS:IP)
 - Memory viewer
 - VRAM viewer
 - Stack display
 - Instruction disassembly display
 - Video card status display
 - 
## Hardware Implementation Status

Currently, XTCE-Blue has emulation of the following devices:

 - Microcode-based Intel 8088/8086 CPU
 - Microcode-based NEC V20/V30 CPU
 - Intel 8253 Programmable Interrupt Timer
 - Intel 8259 Programmable Interrupt Controller
 - Intel 8255 Programmable Peripheral Interface
 - Intel 8237 Programmable DMA Controller
 - IBM Color Graphics Adapter
 - IBM Floppy Disk Controller (NEC u765) 
 - IBM Model F Keyboard

What it is currently lacking:

 - Serial Port(s)
 - Parallel Ports(s)
 - Game Port

## CPU core selection

The default CPU core is **generated-8088**. The **generated** core compiles Intel microcode
into a C++ word switch. The hope was that this would be significantly faster than microcode interpretation; 
unfortunately it isn't. It's still slightly faster though due to ALU call specialization.

The original **interpreted** core from XTCE remains available with `--cpu-core interpreted`:

You can select the core at runtime via:

```
xtce-blue --cpu-core interpreted --cpu-model 8088 
xtce-blue --cpu-core generated --cpu-model 8088
xtce-blue --cpu-core generated --cpu-model 8086
xtce-blue --cpu-core generated --cpu-model v20
xtce-blue --cpu-core generated --cpu-model v30
```

## Single-step tests

XTCE-Blue passes my [8088](https://github.com/SingleStepTests/8088) and [V20](https://github.com/SingleStepTests/v20)
SingleStepTest CPU test suites, 100%, for every cycle trace, including all undefined flags.

You can run a SST suite with `run-tests --test-path <file-or-directory> --test-max 0`.
For every CPU core, `--test-mode architecture` checks registers, all FLAGS bits,
final RAM, and the ordered memory and I/O accesses. `--test-mode cycles` also
checks clock timing and bus/queue signals.

## Floppy Image mounting

Use `--floppy0` to mount a raw floppy image in drive A: before booting:

```
xtce-blue --cpu-core generated --cpu-model v20 --floppy0 "path/to/Disk01.img"
```

## Known issues

 - Some glitches in Area 5150
 - Microsoft Flight Simulator 1.0 fails to load

# Thanks to

 - Ken Shirriff for his invaluable analysis of the 8088
 - Omar Cornut for the excellent Dear ImGui library
 - Blargg for the Blip_Buffer waveform synthesis library
