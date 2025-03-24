//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <imgui.h>
#include <fmt/base.h>

LightMeUpLevel::LightMeUpLevel(): m_lights(64) {

}


void LightMeUpLevel::Init() {
    Level::Init();
    // LtPlayLV.init( LightArr[0], 8 ,  8  , 200, 200, 8, 8, sf::Vector2f(32,32) );
    fmt::println("LightMeUpLevel::Init");
    m_lights.reserve(m_matrixHeight * m_matrixHeight);
    for (auto light : m_lights) {
        light.init(125, 0, 125);
    }
    m_visual.init(m_lights[0], 8, 8, 200, 200, 8, 8, sf::Vector2f(32, 32));
    m_visual.update();
}

void LightMeUpLevel::Destroy() {

}

void LightMeUpLevel::Tick(double deltaTime) {
}

void LightMeUpLevel::Render(sf::RenderTarget &target) {
    m_visual.draw(target);
}

bool EditorVector2f(sf::Vector2f &vec, const char *label, float minx, float miny, float maxx, float maxy) {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR",
    ImVec2(0, 260),
    ImGuiChildFlags_Borders,
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

void LightMeUpLevel::RenderEditor() {

    static sf::Vector2f visualBoxSize = sf::Vector2f(32, 32);

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        if (ImGui::DragInt("Matrix Height", &m_matrixHeight, 0.5f, 1, 18)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("Total Lights: {}", totalLights);
            m_lights.resize(totalLights);
            for (auto light : m_lights) {
                light.init(125, 0, 125);
            }
            m_visual.init(m_lights[0], m_matrixHeight, m_matrixHeight, 200.f, 200.f, 8.f, 8.f, visualBoxSize);
            m_visual.update();
        }
        m_visual.RenderEditor();
        //
        // if (EditorVector2f(visualBoxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
        //     fmt::println("New vector value: {},{}", visualBoxSize.x, visualBoxSize.y);
        //     for (auto light : m_lights) {
        //         light.init(125, 0, 125);
        //     }
        //     m_visual.init(m_lights[0], m_matrixHeight, m_matrixHeight, 200.f, 200.f, 8.f, 8.f, visualBoxSize);
        //     m_visual.update();
        // }


    }
    ImGui::End();

}
