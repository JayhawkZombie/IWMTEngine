//
// Created by Kurt Slagle on 4/6/25.
//

#include <imgui.h>
#include <Logging/LogFormatting.h>
#include <Editor/ImGuiHelpers.h>
#include "LightMeUpLevel.h"

bool LightMeUpLevel::RenderEditor() {
    bool edited = false;
    // static int matrixDim = m_matrixHeight;

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        ImGui::SetNextItemWidth(50.f);
        EditorViewInt("Matrix Height",
                      m_matrixHeight,
                      ImColor(0.5f, 0.5f, 0.5f, 1.f));
        // if (ImGui::DragInt("Matrix Height", &m_matrixHeight, 0.5f, 1, 18)) {
        //     m_matrixWidth = m_matrixHeight;
        //     const auto totalLights = m_matrixHeight * m_matrixHeight;
        //     // m_matrixWidth          = m_matrixHeight;
        //     fmt::println("Total Lights: {}", totalLights);
        //     // ResetAndResizeLights();
        //     // Init();
        // }

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

bool LightMeUpLevel::RenderPatternPlayerEditorTab() {
    // bool edited = false;
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
    EditorViewPatternData("Pattern data",
                          m_lightPlayer2.pattData,
                          m_lightPlayer2.numPatterns,
                          m_lightPlayer2.pattData[ m_lightPlayer2.patternIter ].funcIndex);
    return false;
}

bool LightMeUpLevel::RenderWavePlayerEditorTab() {
    return m_wavePlayerWrapper.RenderEditor();
    // bool edited = false;
    // edited      = EditorLight(m_wavePlayer.loLt, "Lo light");
    // ImGui::SameLine();
    // edited = edited || EditorLight(m_wavePlayer.hiLt, "Hi light");
    // if (ImGui::SliderFloat3("C_Rt", &C_Rt[0], 0.f, 20.f, "%.3f")) {
    //     m_wavePlayer.setSeriesCoeffs(C_Rt, 2, nullptr, 0);
    // }
    // if (ImGui::SliderFloat("Amp Lt", &m_wavePlayer.AmpLt, 0.f, 5.f, "%.3f")) {
    //     edited = true;
    // }
    // if (ImGui::SliderFloat("Amp Rt", &m_wavePlayer.AmpRt, 0.f, 5.f, "%.3f")) {
    //     edited = true;
    // }
    //
    // if (ImGui::SliderFloat("WvLn Lt",
    //                        &m_wavePlayer.wvLenLt,
    //                        0.f,
    //                        128.f,
    //                        "%.3f")) {
    //     edited = true;
    // }
    // if (ImGui::SliderFloat("WvLn Rt",
    //                        &m_wavePlayer.wvLenRt,
    //                        0.f,
    //                        128.f,
    //                        "%.3f")) {
    //     edited = true;
    // }
    //
    // if (ImGui::SliderFloat("WvSpd Lt",
    //                        &m_wavePlayer.wvSpdLt,
    //                        0.f,
    //                        128.f,
    //                        "%.3f")) {
    //     edited = true;
    // }
    // if (ImGui::SliderFloat("WvSpd Rt",
    //                        &m_wavePlayer.wvSpdRt,
    //                        0.f,
    //                        128.f,
    //                        "%.3f")) {
    //     edited = true;
    // }
    //
    // if (edited) {
    //     m_wavePlayer.init(m_lights[0],
    //                       m_matrixHeight,
    //                       m_matrixWidth,
    //                       m_wavePlayer.hiLt,
    //                       m_wavePlayer.loLt);
    // }

    // return edited;
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
    edited = EditorLight(m_lightPlayer2.onLt, "On light");
    ImGui::SameLine();
    edited = edited || EditorLight(m_lightPlayer2.offLt, "Off light");
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
