//
// Created by Kurt Slagle on 1/12/25.
//

#pragma once
#include <Globals.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Level/LightMeUp/Light_types/Light.h>
#include <Level/LightMeUp/Light_types/LightPlayer2.h>
#include <Misc/UI.h>
#include <Utility/MemUtils.h>

inline bool EditorBeginRoundedChild(const char *label, const char *id, bool showLabel = false) {
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

inline bool EditImGuiVector2f(const char *label, sf::Vector2f &v) {
    if (ImGui::BeginChild(label)) {
        // SHOULD be fine, because they are laid out
        // next to each other in memory
        if (ImGui::InputFloat2(label, &v.x)) {
            return true;
        }
    }
    return false;
}

inline bool EditorVector2f(sf::Vector2f &vec,
                           const char *label,
                           float minx,
                           float miny,
                           float maxx,
                           float maxy) {
    bool edited = false;
    EditorBeginRoundedChild(label, "Vector2f");
    ImGui::Indent(5.f);
    ImGui::Text("%s", label);
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::DragFloat("x", &vec.x, 2.f, minx, maxx)) {
        fmt::println("Edited vector x = {}", vec.x);
        edited = true;
    }
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::DragFloat("y", &vec.y, 2.f, miny, maxy)) {
        fmt::println("Edited vector y = {}", vec.y);
        edited = true;
    }

    ImGui::Unindent();
    EditorEndRoundedChild();
    return edited;
}

inline bool EditorLight(Light &light, const char *label) {
    static float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    color[0]              = static_cast<float>(light.r) / 255.0f;
    color[1]              = static_cast<float>(light.g) / 255.0f;
    color[2]              = static_cast<float>(light.b) / 255.0f;
    color[3]              = 1.f;
    bool edited           = false;
    EditorBeginRoundedChild(label, "Light");
    ImGui::Indent(5.f);
    ImGui::Text("%s", label);
    ImGui::SetNextItemWidth(100.f);
    ImGui::SameLine();
    if (ImGui::ColorEdit4(label,
                          color,
                          ImGuiColorEditFlags_NoInputs |
                          ImGuiColorEditFlags_NoLabel)) {
        light.init(
                   static_cast<uint8_t>(color[0] * 255.0f),
                   static_cast<uint8_t>(color[1] * 255.0f),
                   static_cast<uint8_t>(color[2] * 255.0f)
                  );
        edited = true;
    }
    ImGui::Unindent();
    EditorEndRoundedChild();
    return edited;
}

inline void EditorColoredLabeledUnsignedInt(const char *label,
                                            ImColor color,
                                            unsigned int value) {
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::TextColored(color, "%u", value);
}

inline bool EditorComboListbox(const char *label,
                               const std::vector<std::string> &items,
                               unsigned int &selected,
                               bool &changed,
                               ImVec2 size = ImVec2(0, 0)) {
    static int selectedIndex = 0;
    selectedIndex            = static_cast<int>(selected);
    bool edited              = false;
    changed                  = false;
    ImGui::PushID(label);
    ImGui::SetNextItemWidth(50.f);
    ImGui::Text("%s", label);
    ImGui::SetNextItemWidth(350.f);
    if (ImGui::BeginListBox("##ComboDropdown", size)) {
        for (size_t i = 0; i < items.size(); i++) {
            const bool isSelected = selected == i;
            if (ImGui::Selectable(items[i].c_str(), isSelected)) {
                edited        = true;
                selectedIndex = i;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }
    ImGui::PopID();
    if (edited) {
        selected = selectedIndex;
        changed  = true;
    }
    return edited;
}

inline bool EditorShowAlertModal(const char *title, const char *message) {
    bool edited = false;
    if (ImGui::BeginPopupModal(title,
                               nullptr,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(ImGuiColors::ErrorOrange, "%s", message);
        if (ImGui::Button("OK")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
        edited = true;
    }
    return edited;
}

inline bool EditorInputTextWithButton(const char *inputLabel,
                                      char *inputBuff,
                                      size_t inputBuffSize,
                                      const char *buttonText) {
    bool edited = false;
    ImGui::SetNextItemWidth(300.f);
    ImGui::InputText(inputLabel, inputBuff, inputBuffSize);
    ImGui::SameLine();
    ImGui::PushID(inputLabel);
    edited = ImGui::Button(buttonText);
    ImGui::PopID();
    return edited;
}

inline void EditorViewPatternData(const char *label,
                                  const patternData *pdata,
                                  unsigned int numPatterns,
                                  unsigned int currentIndex = 0) {
    EditorBeginRoundedChild(label, "Patterns");
    if (ImGui::BeginTable(label,
                          4,
                          ImGuiTableFlags_Resizable |
                          ImGuiTableFlags_BordersOuter |
                          ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Func index");
        ImGui::TableSetupColumn("Step pause");
        ImGui::TableSetupColumn("Param");
        ImGui::TableSetupColumn("Name");
        ImGui::TableHeadersRow();
        for (unsigned int i = 0; i < numPatterns; i++) {
            ImGui::TableNextRow();
            const auto &p = pdata[i];
            if (p.funcIndex == currentIndex) {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0,
                                       ImColor(255, 255, 0));
            }
            ImColor tColor = p.funcIndex == currentIndex
                                 ? ImColor(0, 0, 0)
                                 : ImColor(255, 255, 255);
            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(tColor, "%u", p.funcIndex);
            ImGui::TableSetColumnIndex(1);
            ImGui::TextColored(tColor, "%u", p.stepPause);
            ImGui::TableSetColumnIndex(2);
            ImGui::TextColored(tColor, "%u", p.param);
            ImGui::TableSetColumnIndex(3);
            ImGui::TextColored(tColor, "%s", PatternNames[p.funcIndex]);
        }
        ImGui::EndTable();
    }
    EditorEndRoundedChild();
}

inline void EditorViewFloat(const char *label,
                            float value,
                            ImColor color = ImColor(1.f, 1.f, 1.f, 1.f)) {
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::TextColored(color, "%.3f", value);
}

inline void EditorViewInt(const char *label,
                          int value,
                          ImColor color = ImColor(1.f, 1.f, 1.f, 1.f)) {
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::TextColored(color, "%i", value);
}

inline bool EditorBoolean(const char *label, bool &value) {
    static bool val;
    val         = value;
    bool edited = false;

    ImGui::Text("%s", label);
    ImGui::SameLine();
    if (ImGui::Checkbox(label, &val)) {
        edited = true;
        value  = val;
    }

    return edited;
}
