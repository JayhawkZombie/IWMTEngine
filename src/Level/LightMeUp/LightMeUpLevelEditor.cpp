//
// Created by Kurt Slagle on 4/6/25.
//

#include <imgui.h>
#include <Logging/LogFormatting.h>
#include <Editor/ImGuiHelpers.h>
#include "LightMeUpLevel.h"

bool LightMeUpLevel::RenderEditor() {
    bool edited = false;

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        ImGui::SetNextItemWidth(50.f);
        if (ImGui::DragInt("Matrix Height", &m_matrixHeight, 0.5f, 1, 18)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            m_matrixWidth          = m_matrixHeight;
            fmt::println("Total Lights: {}", totalLights);
            // ResetAndResizeLights();
            Init();
        }

        if (EditorVector2f(m_boxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
            fmt::println("New vector value: {}", m_boxSize);
            ResetAndResizeLights();
        }
        if (EditorVector2f(m_boxSpacing, "Box Spacing", 1.f, 1.f, 20.f, 20.f)) {
            fmt::println("New vector value: {}", m_boxSpacing);
            ResetAndResizeLights();
        }

        RenderLightsEditor();
    }
    ImGui::End();
    return edited;
}

bool LightMeUpLevel::RenderLightsEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("Pattern Player",
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 ImGui::GetContentRegionAvail().y),
                          ImGuiChildFlags_Borders |
                          ImGuiChildFlags_AlwaysAutoResize |
                          ImGuiChildFlags_AutoResizeY |
                          ImGuiChildFlags_AutoResizeX,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Pattern Player");
        edited = EditorLight(m_lightPlayer2.onLt, "On light");
        ImGui::SameLine();
        edited = edited || EditorLight(m_lightPlayer2.offLt, "Off light");

        ImGui::TextColored(ImColor(255, 0, 0), "State (readonly)");
        ImGui::Separator();
        EditorColoredLabeledUnsignedInt("Num patterns",
                                        ImColor(255, 255, 0),
                                        m_lightPlayer2.numPatterns);
        EditorColoredLabeledUnsignedInt("Pattern iter",
                                        ImColor(255, 255, 0),
                                        m_lightPlayer2.patternIter);
        EditorColoredLabeledUnsignedInt("Step timer  ",
                                        ImColor(255, 255, 0),
                                        m_lightPlayer2.stepTimer);
        EditorColoredLabeledUnsignedInt("Step iter   ",
                                        ImColor(255, 255, 0),
                                        m_lightPlayer2.stepIter);

        ImGui::SeparatorText("Pattern Data");
        EditorViewPatternData("Pattern data", m_lightPlayer2.pattData, m_lightPlayer2.numPatterns);
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}
