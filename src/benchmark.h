// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <SDL3/SDL_init.h>
#include <cstdint>
#include <span>
#include "core/CpuSelection.h"

SDL_AppResult runBenchmark(CpuSelection selection = {}, std::span<const uint8_t> floppy0 = {});
