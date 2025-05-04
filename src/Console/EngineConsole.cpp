#include <Console/EngineConsole.h>
#include <Globals.h>
#include <Misc/IconsFontAwesome6.h>

static int InputTextCallbackStub(ImGuiInputTextCallbackData *data) {
    return GlobalConsole->InputTextCallback(data);
}

EngineConsole::~EngineConsole() {
    {
        if (m_persistToFile) {
            WriteToPersistentFile();
        }
    }
}

void EngineConsole::Tick(double delta) {
}

void EngineConsole::SetPersistentFile(const std::string &filename) {
    m_persistToFile = true;
    m_persistentFilename = filename;
}

void EngineConsole::SetPersistToFile(bool persist) {
    m_persistToFile = persist;
}

void EngineConsole::RenderLogsAndMessages() {
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    const auto winSize = ImGui::GetWindowSize();
    ImGui::TextUnformatted("Messages and Logs");
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_TRASH_CAN)) {
        ClearConsole();
    }
    // How much space do we have left?
    if (ImGui::BeginChild("#logs", {winSize.x * 0.7f - 50.f, winSize.y * 0.9f - footer_height_to_reserve},
                          ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AutoResizeX)) {
        for (const auto &item: m_entries) {
            item.Draw();
        }
        if (m_needsScroll) {
            ImGui::SetScrollHereY(1.0f);
            m_needsScroll = false;
        }
    }
    ImGui::EndChild();
}

void EngineConsole::RenderTerminal() {
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    const float lineHeightToReserve = ImGui::GetTextLineHeightWithSpacing() * 1.f;
    const auto winSize = ImGui::GetWindowSize();
    ImGui::TextUnformatted("Terminal");
    if (ImGui::BeginChild("#terminal", {winSize.x * 0.3f, winSize.y - footer_height_to_reserve - lineHeightToReserve - 50},
                          ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AutoResizeX)) {
        ImGui::Indent(5.f);
        for (int i = 0; i < 20; ++i) {
            ImGui::TextUnformatted("> entry");
        }
    }
    ImGui::EndChild();
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll |
                                           ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    ImGui::PushItemWidth(winSize.x * 0.2);
    if (ImGui::InputText("Input", m_inputBuf, IM_ARRAYSIZE(m_inputBuf), input_text_flags, &InputTextCallbackStub,
                         (void *) this)) {
        char *s = m_inputBuf;
        AddEntry(LogLevel::Info, "%s", m_inputBuf);
        memset(m_inputBuf, '\0', IM_ARRAYSIZE(m_inputBuf));
        m_needsScroll = true;
    }
    ImGui::PopItemWidth();
}

void EngineConsole::Render(sf::RenderTarget &target) {
    // static auto dockspaceId = ImGui::GetID("Editor");
    // ImGui::DockSpaceOverViewport(dockspaceId);
    const auto winSize = target.getSize();
    ImGui::SetNextWindowPos(ImVec2(0.f, winSize.y - 300.f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(winSize.x, 300.f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Console", &m_isOpen, ImGuiWindowFlags_NoScrollbar)) {
        ImGui::BeginGroup();
        RenderLogsAndMessages();
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        RenderTerminal();
        ImGui::EndGroup();
    }
    ImGui::End();


    return;

    // ImGui::SetNextWindowPos(ImVec2(0.f, 550.f), ImGuiCond_FirstUseEver);
    // ImGui::SetNextWindowSize(ImVec2(400.f, 250.f), ImGuiCond_FirstUseEver);
    // if (ImGui::Begin("Console", &m_isOpen, ImGuiWindowFlags_NavFlattened))
    // {
    //     ImGui::TextWrapped("Here is a console, idk what I'm gonna do with it");
    //     ImGui::SeparatorText("Try adding an entry!");
    //     static constexpr const char *log_preview_items[] = {
    //         "INFO",
    //         "DEBUG",
    //         "WARNING",
    //         "ERROR",
    //         "FATAL",
    //     };
    //     static int selected_index = 1;
    //     const auto preview_value = log_preview_items[selected_index];
    //     if (ImGui::BeginCombo("Trace log level", preview_value, ImGuiComboFlags_WidthFitPreview))
    //     {
    //         for (int i = 0; i < sizeof(log_preview_items) / sizeof(char *); ++i)
    //         {
    //             const bool is_selected = (selected_index == i);
    //             if (ImGui::Selectable(log_preview_items[i], is_selected))
    //             {
    //                 selected_index = i;
    //             }
    //             if (is_selected)
    //             {
    //                 ImGui::SetItemDefaultFocus();
    //             }
    //         }
    //         ImGui::EndCombo();
    //     }
    //     ImGui::SameLine();
    //     if (ImGui::Button("Sample entry"))
    //     {
    //         const auto currentTime = GlobalRTC->GetTimeSinceStart();
    //         AddEntry(static_cast<LogLevel>(selected_index), "[%.4lf] Have %lu items", RealTimeClock::ToSeconds(currentTime).count(), m_entries.size());
    //     }
    //     ImGui::Separator();

    //     const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    //     if (ImGui::BeginChild("ScrollingRegion", ImVec2(0.f, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
    //     {
    //         for (const auto &item : m_entries)
    //         {
    //             item.Draw();
    //         }
    //         if (m_needsScroll)
    //         {
    //             ImGui::SetScrollHereY(1.0f);
    //             m_needsScroll = false;
    //         }
    //     }
    //     ImGui::EndChild();
    //     ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    //     if (ImGui::InputText("Input", m_inputBuf, IM_ARRAYSIZE(m_inputBuf), input_text_flags, &InputTextCallbackStub, (void *) this))
    //     {
    //         char *s = m_inputBuf;
    //         AddEntry(LogLevel::Info, "%s", m_inputBuf);
    //         memset(m_inputBuf, '\0', IM_ARRAYSIZE(m_inputBuf));
    //         m_needsScroll = true;
    //     }
    // }
    // ImGui::End();
}

int EngineConsole::InputTextCallback(ImGuiInputTextCallbackData *data) {
    return 0;
}

void EngineConsole::SetOpen(bool open) {
    m_isOpen = open;
}

bool EngineConsole::IsOpen() const {
    return m_isOpen;
}

void EngineConsole::WriteToPersistentFile() {
    std::ofstream outfile(m_persistentFilename);
    if (outfile) {
        for (const auto &entry: m_entries) {
            outfile.write(entry.buf, strnlen(entry.buf, 1024));
            outfile.write("\n", 1);
        }
    }
}

void EngineConsole::ClearConsole() {
    m_entries.clear();
}
