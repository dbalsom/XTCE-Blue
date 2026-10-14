// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#include "GeneratedCpu.h"

namespace marty::nec {

void GeneratedCpu::executeMicrocode(uint16_t address) {
    switch (address) {
        #include "microcode_dispatch.inc"
        default: break;
    }
}

} // namespace marty::nec
