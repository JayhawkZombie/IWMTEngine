//
// Created by Kurt Slagle on 1/12/25.
//

#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <Level/LightMeUp/Light_types/Light.h>
#include <Level/LightMeUp/Light_types/LightPlayer2.h>

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
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::PushID(label);
    ImGui::BeginChild("##ChildR",
                      ImVec2(0, 80),
                      ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY |
                      ImGuiChildFlags_AutoResizeX,
                      ImGuiWindowFlags_None);
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
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopID();
    return edited;
}

inline bool EditorLight(Light &light, const char *label) {
    static float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    color[0]              = static_cast<float>(light.r) / 255.0f;
    color[1]              = static_cast<float>(light.g) / 255.0f;
    color[2]              = static_cast<float>(light.b) / 255.0f;
    color[3]              = 1.f;
    bool edited           = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::PushID(label);
    ImGui::BeginChild("##Light",
                      ImVec2(0, 0),
                      ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY |
                      ImGuiChildFlags_AutoResizeX,
                      ImGuiWindowFlags_None);
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
    ImGui::EndChild();
    ImGui::PopID();
    ImGui::PopStyleVar();
    return edited;
}

inline void EditorColoredLabeledUnsignedInt(const char *label,
                                            ImColor color,
                                            unsigned int value) {
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::TextColored(color, "%u", value);
}

inline void EditorViewPatternData(const char *label,
                                  const patternData *pdata,
                                  unsigned int numPatterns) {
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::PushID(label);
    ImGui::BeginChild("##Light",
                      ImVec2(0, 0),
                      ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY |
                      ImGuiChildFlags_AutoResizeX,
                      ImGuiWindowFlags_None);
    if (ImGui::BeginTable(label,
                          3,
                          ImGuiTableFlags_Resizable |
                          ImGuiTableFlags_BordersOuter |
                          ImGuiTableFlags_ScrollY)) {
        ImGui::TableSetupColumn("Func index");
        ImGui::TableSetupColumn("Step pause");
        ImGui::TableSetupColumn("Param");
        ImGui::TableHeadersRow();
        for (unsigned int i = 0; i < numPatterns; i++) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            const auto &p = pdata[i];
            ImGui::Text("%u", p.funcIndex);
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", p.stepPause);
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%u", p.param);
        }
        ImGui::EndTable();
    }
    ImGui::EndChild();
    ImGui::PopID();
    ImGui::PopStyleVar();
}

inline void EditorViewFloat(const char *label, float value, ImColor color = ImColor(1.f, 1.f, 1.f, 1.f)) {
    ImGui::Text("%s", label);
    ImGui::SameLine();
    ImGui::TextColored(color, "%.3f", value);
}

inline bool EditorBoolean(const char *label, bool &value) {
    static bool val;
    val = value;
    bool edited = false;

    ImGui::Text("%s", label);
    ImGui::SameLine();
    if (ImGui::Checkbox(label, &val)) {
        edited = true;
        value = val;
    }

    return edited;
}

namespace ImGuiColors {
    static constexpr ImVec4 BrightBlue    = ImVec4(0.149, 0.988f, 0.953f, 1.f);
    static constexpr ImVec4 BrightPink    = ImVec4(1.f, 0.f, 0.929f, 1.f);
    static constexpr ImVec4 MutedMagenta  = ImVec4(0.808f, 0.22f, 0.812f, 1.f);
    static constexpr ImVec4 InfoGray      = ImVec4(0.729f, 0.729f, 0.729f, 1.f);
    static constexpr ImVec4 DebugBlue     = ImVec4(0.f, 0.627f, 0.839f, 1.f);
    static constexpr ImVec4 WarningYellow = ImVec4(1.f, 1.f, 0.f, 1.f);
    static constexpr ImVec4 ErrorOrange   = ImVec4(1.f, 0.569f, 0.f, 1.f);
    static constexpr ImVec4 FatalRed      = ImVec4(0.91f, 0.165f, 0.f, 1.f);
}
