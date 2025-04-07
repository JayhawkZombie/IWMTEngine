//
// Created by Kurt Slagle on 1/12/25.
//

#include "TarmieLevel.h"

#include <imgui.h>
#include <Logging/LogFormatting.h>

TarmieLevel::TarmieLevel() {
}

TarmieLevel::~TarmieLevel() {
}

void TarmieLevel::Init() {
    Level::Init();
    fmt::println("{}",
                 fmt::styled("TarmieLevel::Init()",
                             fg_color_lavender | fmt::emphasis::italic));
    m_spriteSheet.Load("tiles.png");
}

void TarmieLevel::Render(sf::RenderTarget &target) {
    Level::Render(target);
    // m_spriteSheet.Render(target, {0.f, 0.f});
    const auto mPos = sf::Mouse::getPosition();
    RenderGrid(target);
    const auto gPos = GetGridCoord(mPos);
    sf::RectangleShape mRect;
    mRect.setPosition(gPos.x, gPos.y);
    mRect.setFillColor(sf::Color::Green);
    target.draw(mRect);
}

void TarmieLevel::RenderGrid(sf::RenderTarget &target) {
    // rRW.draw(&(vtxVec[0]), vtxVec.size(), sf::LinesStrip);
    target.draw(&(m_gridLineVertices[0]),
                m_gridLineVertices.size(),
                sf::LinesStrip);
}

bool TarmieLevel::RenderEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR",
                      ImVec2(0, 260),
                      ImGuiChildFlags_Borders,
                      ImGuiWindowFlags_ChildWindow);
    ImGui::Text("Tarmie");
    ImGui::SeparatorText("World Params");
    if (ImGui::DragInt("Block size",
                       &m_worldBlockSizePx,
                       1.f,
                       5.f,
                       150.f,
                       "%i",
                       ImGuiSliderFlags_AlwaysClamp)) {
        edited = true;
        AdjustToNewBlockSize();
    }
    ImGui::SeparatorText("Sprite Sheet");
    m_spriteSheet.RenderEditor();
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

void TarmieLevel::Tick(double delta) {
    Level::Tick(delta);
}

void TarmieLevel::AdjustToNewBlockSize() {
    // Recreate grid lines
    CreateGridLines();
}

void TarmieLevel::CreateGridLines() {
    m_gridLineVertices.clear();

    for (int x = 0; x < 10; x++) {
        // Vertical lines
        sf::Vertex vertex;
        vertex.position.x = static_cast<float>(x * m_worldBlockSizePx);
        vertex.position.y = static_cast<float>(0);
        vertex.color      = sf::Color::Blue;
        m_gridLineVertices.push_back(vertex);

        vertex.position.y = 900.f;
        m_gridLineVertices.push_back(vertex);
    }
}

sf::Vector2i TarmieLevel::GetGridCoord(const sf::Vector2i &pos) {
    // Just gets the coord that would be in the world grid, given a (x,y) position
    const auto XCoord = pos.x / m_worldBlockSizePx; // Truncation is intended
    const auto YCoord = pos.y / m_worldBlockSizePx;
    return sf::Vector2i(XCoord, YCoord);
}
