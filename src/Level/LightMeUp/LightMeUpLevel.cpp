//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <Globals.h>
#include <imgui.h>
#include <fmt/base.h>

LightMeUpLevel::LightMeUpLevel() {
    m_lightStates.emplace_back();
    m_lightStates.front().resize(64, Light(125, 125, 125));
    m_visual.init(m_lightStates.front().data(),
                  8,
                  8,
                  200.f,
                  200.f,
                  8.f,
                  8.f,
                  sf::Vector2f(32, 32));
}


void LightMeUpLevel::Init() {
    Level::Init();
    // LtPlayLV.init( LightArr[0], 8 ,  8  , 200, 200, 8, 8, sf::Vector2f(32,32) );
    fmt::println("LightMeUpLevel::Init");
    m_lightStates.emplace_back();
    auto &lights = m_lightStates.front();
    lights.reserve(m_matrixHeight * m_matrixHeight);
    for (auto light: lights) {
        light.init(125, 125, 125);
    }
    m_visual.init(lights.data(), 8, 8, 200, 200, 8, 8, sf::Vector2f(32, 32));
    m_visual.update();
}

void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
}

void LightMeUpLevel::Render(sf::RenderTarget &target) {
    m_visual.draw(target);
}

bool EditorVector2f(sf::Vector2f &vec,
                    const char *label,
                    float minx,
                    float miny,
                    float maxx,
                    float maxy) {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR",
                      ImVec2(0, 80),
                      ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,
                      ImGuiWindowFlags_None);
    ImGui::Indent(5.f);
    if (ImGui::DragFloat("x", &vec.x, 2.f, minx, maxx)) {
        fmt::println("Edited vector x = {}", vec.x);
        edited = true;
    }

    if (ImGui::DragFloat("y", &vec.y, 2.f, miny, maxy)) {
        fmt::println("Edited vector y = {}", vec.y);
        edited = true;
    }

    ImGui::Unindent();
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

void LightMeUpLevel::ResetAndResizeLights(size_t size,
                                          float posX,
                                          float posY,
                                          float dPosX,
                                          float dPosY,
                                          const sf::Vector2f &boxSize) {
    for (auto &lightVec: m_lightStates) {
        lightVec.resize(size, Light(125, 125, 125));
    }

    auto &lVec = m_lightStates[m_editorSelectedStateIndex];
    m_visual.init(lVec.data(),
                  m_matrixHeight,
                  m_matrixHeight,
                  posX,
                  posY,
                  dPosX,
                  dPosY,
                  boxSize);
    m_visual.update();
}


void LightMeUpLevel::RenderEditor() {
    static sf::Vector2f visualBoxSize = sf::Vector2f(32, 32);

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        ImGui::SetNextItemWidth(100.f);
        if (ImGui::DragInt("Matrix Height", &m_matrixHeight, 0.5f, 1, 18)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("Total Lights: {}", totalLights);
            ResetAndResizeLights(totalLights,
                                 200.f,
                                 200.f,
                                 8.f,
                                 8.f,
                                 visualBoxSize);
        }
        ImGui::SameLine();

        if (EditorVector2f(visualBoxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("New vector value: {},{}",
                         visualBoxSize.x,
                         visualBoxSize.y);
            ResetAndResizeLights(totalLights,
                                 200.f,
                                 200.f,
                                 8.f,
                                 8.f,
                                 visualBoxSize);
        }
        RenderLightStatesSelectorEditor();
        RenderLightsEditor();
    }
    ImGui::End();
}

bool LightMeUpLevel::RenderLightsEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("ChildLightsEditor",
                          // ImVec2(0, 0),
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 ImGui::GetContentRegionAvail().y),
                          ImGuiChildFlags_Borders |
                          ImGuiChildFlags_AlwaysAutoResize |
                          ImGuiChildFlags_AutoResizeY |
                          ImGuiChildFlags_AutoResizeX,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Light colors: ");
        ImGui::Separator();
        edited = true;
        if (m_editorSelectedStateIndex >= m_lightStates.size()) {
            // How the fuck
            GlobalConsole->
                    Error("Selected light state index out of bounds %lu/%lu",
                          m_editorSelectedStateIndex,
                          m_lightStates.size());
        } else {
            ImGui::BeginTable("Light colors",
                              8,
                              ImGuiTableFlags_Borders);
            if (m_editorSelectedStateIndex >= m_lightStates.size()) {
                ImGui::Text("Invalid light state index");
                ImGui::SameLine();
                if (ImGui::Button("Reset")) {
                    m_editorSelectedStateIndex = 0;
                }
            } else {
                light_vector &lights = m_lightStates[
                    m_editorSelectedStateIndex];

                for (auto &light: lights) {
                    ImGui::TableNextColumn();
                    light.RenderEditor();
                }
            }
            ImGui::EndTable();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

bool LightMeUpLevel::RenderLightStatesSelectorEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("LightStatesEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 100.f),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Light states");
        ImGui::Separator();
        edited = true;
        for (size_t i = 0; i < m_lightStates.size(); ++i) {
            ImGui::PushID(i);
            ImGui::PushStyleColor(ImGuiCol_Button,
                                  static_cast<ImVec4>(ImColor::HSV(i / 7.0f,
                                      0.6f,
                                      0.6f)));
            if (ImGui::Button("##button", ImVec2(50.f, 50.f))) {
                m_editorSelectedStateIndex = i;
            }
            ImGui::PopStyleColor();
            ImGui::PopID();
            ImGui::SameLine();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}
