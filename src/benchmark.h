// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once

#include <SDL3/SDL_init.h>
#include "core/CpuSelection.h"

SDL_AppResult runBenchmark(CpuSelection selection = {});
