#include "CycleLogWindow.h"
#include <string_view>
#include "../core/Logger.h"
#include "../core/Machine.h"

namespace
{

std::string cycleLogHeader() {
    std::string header(Logger::kMicrocodeColumn + sizeof("MICROCODE") - 1, ' ');
    const auto place = [&](size_t column, std::string_view label)
    { header.replace(column, label.size(), label.data(), label.size()); };

    place(0, "A");
    place(2, "BUS");
    place(8, "CPU");
    place(14, "D");
    place(17, "BUS");
    place(22, "Q/CTL");
    place(30, "DMA");
    place(34, "IRQ");
    place(38, "P");
    place(40, "C");
    place(42, "STROBES");
    place(51, "T");
    place(54, "DS");
    place(58, "QUEUE");
    place(68, "TRANSFER");
    place(86, "Q");
    place(Logger::kDisassemblyColumn, "DISASSEMBLY");
    place(Logger::kMicrocodeColumn, "MICROCODE");
    return header;
}

} // namespace

void CycleLogWindow::show(bool* open) {

    IM_ASSERT(ImGui::GetCurrentContext() != nullptr);

    // ReSharper disable once CppDFAConstantConditions
    if (!_machine) {
        ImGui::Begin("Cycle Log", open);
        ImGui::Text("No Machine instance");
        ImGui::End();
        return;
    }

    // ReSharper disable once CppDFAUnreachableCode
    ImGui::Begin("Cycle Log", open);

    // Controls: enable logging checkbox, clear, capacity
    bool logging = _machine->isCycleLogging();
    if (ImGui::Checkbox("Enable Logging", &logging)) {
        _machine->setCycleLogging(logging);
        if (logging) {
            _machine->clearCycleLog();
            _machine->appendCycleLogLine("--- Cycle logging enabled ---");
            SDL_Log("Cycle logging enabled");
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        _machine->clearCycleLog();
    }
    ImGui::SameLine();
    if (ImGui::Checkbox("Auto-scroll", &_autoScroll) && _autoScroll) {
        // Follow immediately, even when no new entries have arrived while paused.
        _lastSeenRevision.reset();
    }

    ImGui::SameLine();
    ImGui::Text("Capacity:");
    ImGui::SameLine();
    if (ImGui::InputInt("##capacity", &_capacityUI, 0, 1000)) {
        if (_capacityUI < 0) {
            _capacityUI = 0;
        }
        _machine->setCycleLogCapacity(static_cast<size_t>(_capacityUI));
    }

    const bool main_text_changed = ImGui::Checkbox("Main log text", &show_main_text_);
    ImGui::SameLine();
    const bool microcode_changed = ImGui::Checkbox("Microcode disassembly", &show_microcode_);

    ImGui::Separator();
    ImGui::Text("Lines: %llu", static_cast<unsigned long long>(_machine->getCycleLogSize()));
    ImGui::Separator();

    if (!show_main_text_ && !show_microcode_) {
        ImGui::TextDisabled("Select Main log text or Microcode disassembly to display entries.");
        ImGui::End();
        return;
    }

    // A frozen table row stays visible while sharing the log's horizontal scroll.
    const auto& buf = _machine->getCycleLogBuffer();
    static const std::string full_header = cycleLogHeader();
    std::string_view header = full_header;
    if (!show_main_text_) {
        header.remove_prefix(Logger::kMicrocodeColumn);
    }
    else if (!show_microcode_) {
        header = header.substr(0, Logger::kMicrocodeColumn);
    }
    const auto description_for = [&](const CycleLogEntry& entry)
    {
        return show_microcode_ && entry.microcode ? _machine->getMicrocodeDisassembly(entry.microcode->address)
                                                  : std::string_view{};
    };
    size_t description_width = 0;
    for (const auto& entry : buf) {
        description_width = std::max(description_width, description_for(entry).size());
    }
    size_t longest = header.size();
    for (const auto& entry : buf) {
        longest = std::max(
            longest,
            CycleLogMicrocode::formattedSize(entry, description_for(entry), show_main_text_, description_width));
    }

    // The log uses fixed-width columns. Measure length of longest content
    const float content_width = longest * ImGui::CalcTextSize("M").x + ImGui::GetStyle().CellPadding.x * 2;
    const ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;
    if (ImGui::BeginTable("##cyclelog_table", 1, flags, ImVec2(0, 0), content_width)) {
        if (main_text_changed || microcode_changed) {
            ImGui::SetScrollX(0.0f);
        }
        ImGui::TableSetupColumn("##line", ImGuiTableColumnFlags_WidthFixed, content_width);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted(header.data(), header.data() + header.size());

        const auto revision = _machine->getCycleLogRevision();
        const bool scroll_to_end = _autoScroll && !buf.empty() && revision != _lastSeenRevision;

        ImGuiListClipper clipper;
        clipper.Begin(static_cast<int>(buf.size()));
        if (scroll_to_end) {
            clipper.IncludeItemByIndex(static_cast<int>(buf.size() - 1));
        }
        while (clipper.Step()) {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                CycleLogMicrocode::format(buf[i], description_for(buf[i]), _lineBuffer, show_main_text_,
                                          description_width);
                ImGui::TextUnformatted(_lineBuffer.c_str());
                if (scroll_to_end && static_cast<size_t>(i) == buf.size() - 1) {
                    ImGui::SetScrollHereY(1.0f);
                }
            }
        }
        _lastSeenRevision = revision;
        ImGui::EndTable();
    }

    ImGui::End();
}
