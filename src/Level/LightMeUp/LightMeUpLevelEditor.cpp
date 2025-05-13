//
// Created by Kurt Slagle on 4/6/25.
//

#include <imgui.h>
#include <Logging/LogFormatting.h>
#include <Editor/ImGuiHelpers.h>
#include "LightMeUpLevel.h"
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>
#include <GeneratedSerializationData.h>

bool LightMeUpLevel::RenderEditor() {
    bool edited = false;

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        ImGui::SetNextItemWidth(50.f);
        EditorViewInt("Matrix Height",
                      m_matrixHeight,
                      ImColor(0.5f, 0.5f, 0.5f, 1.f));

        if (EditorVector2f(m_boxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
            fmt::println("New vector value: {}", m_boxSize);
            ResetAndResizeLights();
        }
        ImGui::SameLine();
        if (EditorVector2f(m_boxSpacing, "Box Spacing", 1.f, 1.f, 20.f, 20.f)) {
            fmt::println("New vector value: {}", m_boxSpacing);
            ResetAndResizeLights();
        }
        if (EditorLight(m_backgroundColor, "Background Color")) {
            edited = true;
        }
        RenderLightsEditor();
    }
    ImGui::End();
    return edited;
}

bool LightMeUpLevel::RenderPatternPlayerEditorTab() {
    bool edited = false;
    ImGui::TextColored(ImColor(255, 0, 0), "State (readonly)");
    static char outputFileBuff[256] = {0};
    if (ImGui::InputText("Output file", outputFileBuff, 256)) {
        edited = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save")) {
        edited = true;
        InitPatternConfig ipc;
        ipc.rows        = m_matrixWidth;
        ipc.cols        = m_matrixHeight;
        ipc.numPatterns = m_lightPlayer2.numPatterns;
        ipc.pd          = m_patternData;
        ipc.lightSize   = m_boxSize;
        ipc.posX        = m_boxPosition.x;
        ipc.posY        = m_boxPosition.y;
        ipc.dPosX       = m_boxSpacing.x;
        ipc.dPosY       = m_boxSpacing.y;
        std::ofstream outfile(outputFileBuff);
        if (!outfile) {
            GlobalConsole->Error("Could not save file writing %s",
                                 outputFileBuff);
        } else {
            try {
                cereal::JSONOutputArchive archive(outfile);
                archive(cereal::make_nvp("InitPatternConfig", ipc));
            } catch (...) {
                GlobalConsole->Error("Could not save file writing %s", outputFileBuff);
            }
        }
    }
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
    EditorViewPatternData("Pattern data",
                          m_lightPlayer2.pattData,
                          m_lightPlayer2.numPatterns,
                          m_lightPlayer2.pattData[m_lightPlayer2.patternIter].
                          funcIndex);
    return edited;
}

bool LightMeUpLevel::RenderWavePlayerEditorTab() {
    return m_wavePlayerWrapper.RenderEditor();
}

bool LightMeUpLevel::RenderPulsePlayerEditorTab() {
    bool edited = false;
    edited      = m_pulsePlayerWrapper.RenderEditor();
    return edited;
}

bool LightMeUpLevel::RenderDataPlayerEditorTab() {
    return m_dataPlayerWrapper.RenderEditor();
}


bool LightMeUpLevel::RenderLightsEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (EditorLight(m_lightPlayer2.onLt, "On light")) {
        edited = true;
    }
    ImGui::SameLine();
    if (EditorLight(m_lightPlayer2.offLt, "Off light")) {
        edited = true;
    }
    if (ImGui::BeginTabBar("Light Players")) {
        if (ImGui::BeginTabItem("Pattern Player")) {
            edited = RenderPatternPlayerEditorTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Wave Player")) {
            edited = RenderWavePlayerEditorTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Pulse Player")) {
            edited = RenderPulsePlayerEditorTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(("Data Player"))) {
            edited = m_dataPlayerWrapper.RenderEditor();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::PopStyleVar();
    return edited;
}
