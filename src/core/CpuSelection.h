// SPDX-License-Identifier: MIT
// Copyright (C) 2026 Daniel Balsom
#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

enum class CpuExecution { Interpreted, Generated };
enum class CpuFamily { Intel, Nec };
enum class CpuModel { Intel8088, Intel8086, NecV20, NecV30 };

struct CpuSelection {
    CpuExecution execution = CpuExecution::Generated;
    CpuModel model = CpuModel::Intel8088;
};

inline CpuFamily cpuFamily(CpuModel model) {
    switch (model) {
        case CpuModel::Intel8088:
        case CpuModel::Intel8086: return CpuFamily::Intel;
        case CpuModel::NecV20:
        case CpuModel::NecV30: return CpuFamily::Nec;
    }
    throw std::invalid_argument("Unknown CPU model");
}

inline std::string_view cpuModelName(CpuModel model) {
    switch (model) {
        case CpuModel::Intel8088: return "8088";
        case CpuModel::Intel8086: return "8086";
        case CpuModel::NecV20: return "v20";
        case CpuModel::NecV30: return "v30";
    }
    throw std::invalid_argument("Unknown CPU model");
}

inline std::string_view cpuExecutionName(CpuExecution execution) {
    switch (execution) {
        case CpuExecution::Interpreted: return "interpreted";
        case CpuExecution::Generated: return "generated";
    }
    throw std::invalid_argument("Unknown CPU execution method");
}

inline CpuSelection parseCpuSelection(std::string_view execution, std::string_view model) {
    CpuSelection selection;
    if (execution == "interpreted") {
        selection.execution = CpuExecution::Interpreted;
    }
    else if (execution == "generated") {
        selection.execution = CpuExecution::Generated;
    }
    else {
        throw std::invalid_argument("CPU core must be interpreted or generated");
    }
    if (model == "8088") {
        selection.model = CpuModel::Intel8088;
    }
    else if (model == "8086") {
        selection.model = CpuModel::Intel8086;
    }
    else if (model == "v20" || model == "V20") {
        selection.model = CpuModel::NecV20;
    }
    else if (model == "v30" || model == "V30") {
        selection.model = CpuModel::NecV30;
    }
    else {
        throw std::invalid_argument("CPU model must be 8088, 8086, v20 or v30");
    }
    return selection;
}

inline std::string cpuSelectionId(CpuSelection selection) {
    return std::string(cpuExecutionName(selection.execution)) + "-" + std::string(cpuModelName(selection.model));
}

inline std::string cpuSelectionName(CpuSelection selection) {
    std::string model;
    switch (selection.model) {
        case CpuModel::Intel8088: model = "Intel 8088"; break;
        case CpuModel::Intel8086: model = "Intel 8086"; break;
        case CpuModel::NecV20: model = "NEC V20"; break;
        case CpuModel::NecV30: model = "NEC V30"; break;
        default: throw std::invalid_argument("Unknown CPU model");
    }
    return model + " (" + std::string(cpuExecutionName(selection.execution)) + ")";
}

inline void validateMachineCpu(CpuSelection selection) {
    cpuExecutionName(selection.execution);
    if (cpuFamily(selection.model) == CpuFamily::Nec && selection.execution == CpuExecution::Interpreted) {
        throw std::invalid_argument("NEC V20/V30 support is generated only; no interpreted NEC core is planned");
    }
    if (selection.model != CpuModel::Intel8088) {
        throw std::invalid_argument(cpuSelectionId(selection) +
            " is not available in this XTCE machine. Available: interpreted-8088, generated-8088");
    }
}
