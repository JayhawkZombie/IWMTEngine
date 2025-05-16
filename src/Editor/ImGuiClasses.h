//
// Created by Kurt Slagle on 5/4/25.
//

#pragma once

#include "ImGuiHelpers.h"

/*
*inline bool EditorBeginRoundedChild(const char *label, const char *id, bool showLabel = false) {
ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
ImGui::PushID(label);
bool edited = ImGui::BeginChild(id,
ImVec2(0, 0),
ImGuiChildFlags_Borders |
ImGuiChildFlags_AutoResizeY |
ImGuiChildFlags_AutoResizeX,
ImGuiWindowFlags_None);
if (showLabel) {
ImGui::TextColored(ImGuiColors::MutedMagenta, "%s", label);
}
return edited;
}

inline bool EditorEndRoundedChild() {
ImGui::EndChild();
ImGui::PopID();
ImGui::PopStyleVar();
return false;
}
*/

namespace ImGuiHelpers {

    class Group {
    public:
        const char *m_label;
        const char *m_id;
        bool m_showLabel = false;
        bool m_showing = false;

        Group(const char *label, const char *id, bool showLabel = false): m_label(label), m_id(id) {
            ImGui::BeginGroup();
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::PushID(label);
            m_showing = ImGui::BeginChild(id,
                                            ImVec2(0, 0),
                                            ImGuiChildFlags_Borders |
                                            ImGuiChildFlags_AutoResizeY |
                                            ImGuiChildFlags_AutoResizeX,
                                            ImGuiWindowFlags_None | ImGuiWindowFlags_AlwaysVerticalScrollbar);
            if (showLabel) {
                ImGui::TextColored(ImGuiColors::MutedMagenta, "%s", label);
            }
        }

        explicit operator bool() const { return m_showing; }

        ~Group() {
            ImGui::EndChild();
            ImGui::PopID();
            ImGui::PopStyleVar();
            ImGui::EndGroup();
        }
    };

}
