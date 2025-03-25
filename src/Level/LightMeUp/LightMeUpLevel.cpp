//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <imgui.h>
#include <fmt/base.h>

LightMeUpLevel::LightMeUpLevel(): m_lights(64, Light(125, 125, 125)),
                                  m_visual{
                                      m_lights.data(),
                                      8,
                                      8,
                                      200.f,
                                      200.f,
                                      8.f,
                                      8.f,
                                      sf::Vector2f(32, 32)
                                  } {
}


void LightMeUpLevel::Init() {
    Level::Init();
    // LtPlayLV.init( LightArr[0], 8 ,  8  , 200, 200, 8, 8, sf::Vector2f(32,32) );
    fmt::println("LightMeUpLevel::Init");
    m_lights.reserve(m_matrixHeight * m_matrixHeight);
    for (auto light: m_lights) {
        light.init(125, 125, 125);
    }
    m_visual.init(m_lights.data(), 8, 8, 200, 200, 8, 8, sf::Vector2f(32, 32));
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

void LightMeUpLevel::ResetAndResizeLights(size_t size, float posX, float posY, float dPosX, float dPosY, const sf::Vector2f &boxSize) {
    m_lights.resize(size, Light(125, 125, 125));
    m_visual.init(m_lights.data(),
              m_matrixHeight,
              m_matrixHeight,
              posX, posY, dPosX, dPosY,
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
            ResetAndResizeLights(totalLights, 200.f, 200.f, 8.f, 8.f, visualBoxSize);
        }
        ImGui::SameLine();

        if (EditorVector2f(visualBoxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("New vector value: {},{}", visualBoxSize.x, visualBoxSize.y);
            ResetAndResizeLights(totalLights, 200.f, 200.f, 8.f, 8.f, visualBoxSize);
        }

        RenderLightsEditor();
    }
    ImGui::End();
}

void LightMeUpLevel::RenderLightsEditor() {
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("ChildLightsEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 ImGui::GetContentRegionAvail().y),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Light colors: ");
        ImGui::Separator();
        ImGui::BeginTable("Light colors", 8, ImGuiTableFlags_Borders);
        for (auto &light : m_lights) {
            ImGui::TableNextColumn();
            if (light.RenderEditor()) {
                m_visual.update();
            }
        }
        ImGui::EndTable();
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

