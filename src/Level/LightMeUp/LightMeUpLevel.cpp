//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <Globals.h>
#include <imgui.h>
#include <fmt/base.h>
#include <random>
#include <Logging/LogFormatting.h>

LightMeUpLevel::LightMeUpLevel() 
    : m_starrySky(5)  // Initialize with 15 stars per cell
    , m_rng(std::random_device()())  // Initialize RNG with random seed
{
    InitPatterns();
    ResetAndResizeLights();
}

void LightMeUpLevel::Init() {
    Level::Init();
    fmt::println("LightMeUpLevel::Init");

    InitPatterns();
    ResetAndResizeLights();
}

void LightMeUpLevel::InitPatterns() {
    std::ifstream file("testdata.txt");
    if (!file) {
        GlobalConsole->Error("No init file testdata.txt for patterns");
        return;
    }

    unsigned int rows, cols;
    file >> rows >> cols;

    float posX, posY, dPosX, dPosY;
    file >> posX >> posY >> dPosX >> dPosY;
    sf::Vector2f lightSize;
    file >> lightSize.x >> lightSize.y;

    m_matrixWidth = static_cast<int>(cols);
    m_matrixHeight = static_cast<int>(rows);
    m_boxSize = lightSize;
    m_boxPosition = sf::Vector2f(posX, posY);
    m_boxSpacing = sf::Vector2f(dPosX, dPosY);

    unsigned int numPatterns;
    file >> numPatterns;
    m_patternData.reserve(numPatterns);

    patternData pd;
    for (int i = 0; i < numPatterns; ++i) {
        file >> pd.funcIndex >> pd.stepPause >> pd.param;
        m_patternData.push_back(pd);
    }
    ResetAndResizeLights();

    m_lightPlayer2.init(m_lights[0], m_matrixHeight, m_matrixWidth, m_patternData[0], numPatterns);
    m_lightPlayer2.onLt = Light(0, 255, 255);
    m_lightPlayer2.offLt = Light(255,0,255);

    m_lightPlayer2.update();
    m_visual.update();
}


void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
    m_lightPlayer2.update();
    m_visual.update();
    m_starrySky.update(static_cast<float>(deltaTime));

    // Update star cell visibility and color based on LED states
    for (size_t y = 0; y < 8; ++y) {
        for (size_t x = 0; x < 8; ++x) {
            const auto& light = m_lights[y * 8 + x];
            // Calculate visibility based on average brightness
            float brightness = (light.r + light.g + light.b) / (3.0f * 255.0f);
            m_starrySky.setCellVisibility(x, y, brightness);
            // Set color directly from the LED
            m_starrySky.setCellColor(x, y, sf::Color(light.r, light.g, light.b));
        }
    }
}

void LightMeUpLevel::Render(sf::RenderTarget &target) {
    // Get the bounds of the light grid
    sf::FloatRect lightBounds = m_visual.getRect();
    // Add some padding around the lights for the starry background

    lightBounds.left += 400.f;
    lightBounds.top = 400.f;
    lightBounds.width = 300.f;
    lightBounds.height = 300.f;
    
    // Draw starry sky with background in the light grid area
    m_starrySky.draw(target, lightBounds);
    // Then draw the light visualization on top
    m_visual.draw(target);
}

sf::Vector2f LightMeUpLevel::GetLEDsPosition() const {
    return m_boxPosition;
}

void LightMeUpLevel::SetLEDsPosition(const sf::Vector2f &pos) {
    m_boxPosition = pos;
    ResetAndResizeLights();
}

void LightMeUpLevel::ResetAndResizeLights() {
    m_lights.resize(m_matrixWidth * m_matrixHeight, Light(125, 125, 125));
    m_visual.init(m_lights[0],
                  m_matrixHeight,
                  m_matrixWidth,
                  m_boxPosition.x,
                  m_boxPosition.y,
                  m_boxSpacing.x,
                  m_boxSpacing.y,
                  m_boxSize);
    AssignRandomColors();
    m_visual.update();
}

void LightMeUpLevel::AssignRandomColors() {
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    for (auto& light : m_lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
    }
}



