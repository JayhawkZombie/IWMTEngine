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
    : m_starrySky(5) // Initialize with 15 stars per cell
     ,
      m_rng(std::random_device()()) // Initialize RNG with random seed
{
}

void LightMeUpLevel::Init() {
    Level::Init();
    name = "LightMeUpLevel";
    fmt::println("LightMeUpLevel::Init");

    InitPatterns();
    ResetAndResizeLights();
    m_choreography.Init(m_wavePlayerWrapper.GetLights().data());
    m_choreography.Start();
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

    m_matrixWidth  = static_cast<int>(cols);
    m_matrixHeight = static_cast<int>(rows);
    m_boxSize      = lightSize;
    m_boxPosition  = sf::Vector2f(posX, posY);
    m_boxSpacing   = sf::Vector2f(dPosX, dPosY);

    unsigned int numPatterns;
    file >> numPatterns;
    m_patternData.reserve(numPatterns);

    patternData pd;
    for (int i = 0; i < numPatterns; ++i) {
        file >> pd.funcIndex >> pd.stepPause >> pd.param;
        m_patternData.push_back(pd);
    }
    ResetAndResizeLights();

    m_lightPlayer2.init(m_lights[0],
                        m_matrixHeight,
                        m_matrixWidth,
                        m_patternData[0],
                        numPatterns);
    m_lightPlayer2.onLt  = Light(0, 255, 255);
    m_lightPlayer2.offLt = Light(255, 0, 255);

    m_lightPlayer2.update();
}

void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
    UpdateVisuals(deltaTime);

    // Update star cell visibility and color based on LED states
    auto &dpLights = m_dataPlayerWrapper.GetLights();
    m_choreography.Update(deltaTime);
    for (size_t y = 0; y < 8; ++y) {
        for (size_t x = 0; x < 8; ++x) {
            const auto &light = dpLights[y * 8 + x];
            // Calculate visibility based on average brightness
            float brightness = (light.r + light.g + light.b) / (3.0f * 255.0f);
            m_starrySky.setCellVisibility(x, y, brightness);
            // Set color directly from the LED
            m_starrySky.
                    setCellColor(x, y, sf::Color(light.r, light.g, light.b));
        }
    }
}

void LightMeUpLevel::UpdateVisuals(double delta) {
    m_lightPlayer2.update();
    m_visual.update();
    m_starrySky.update(static_cast<float>(delta));
    m_wavePlayerWrapper.Tick(delta);
    m_pulsePlayerWrapper.Tick(delta);
    m_dataPlayerWrapper.Tick(delta);
}


void LightMeUpLevel::Render(sf::RenderTarget &target) {
    // Get the bounds of the light grid
    sf::FloatRect lightBounds = m_visual.getRect();
    sf::RectangleShape box;
    box.setSize(static_cast<sf::Vector2f>(target.getSize()));
    box.setPosition({0.f, 0.f});
    box.setFillColor({m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b});
    // Add some padding around the lights for the starry background
    target.draw(box);

    lightBounds.left += lightBounds.width + 50.f;
    lightBounds.top    = 400.f;
    lightBounds.width  = 300.f;
    lightBounds.height = 300.f;

    // Draw starry sky with background in the light grid area
    m_starrySky.draw(target, lightBounds);
    // Then draw the light visualization on top
    RenderVisuals(target);
}

void LightMeUpLevel::RenderVisuals(sf::RenderTarget &target) {
    m_visual.draw(target);
    m_dataPlayerWrapper.Render(target);
    m_wavePlayerWrapper.Render(target);
    m_pulsePlayerWrapper.Render(target);
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
    // m_visual.initRing(m_lights[0], 64, 100.f, 100.f, 100.f, 5.f, 5.f, m_boxSize);
    AssignRandomColors();
    m_visual.update();
    WavePlayerConfig config;
    config.rows     = m_matrixHeight * 2;
    config.cols     = m_matrixWidth * 2;
    config.onLight  = Light(0, 255, 255);
    config.offLight = Light(255, 0, 255);
    config.C_Rt[0]  = C_Rt[0];
    config.C_Rt[1]  = C_Rt[1];
    config.C_Rt[2]  = C_Rt[2];
    config.AmpLt    = 0.5f;
    config.AmpRt    = 0.5f;
    config.wvLenLt  = 64.f;
    config.wvLenRt  = 64.f;
    config.wvSpdLt  = 128.f;
    config.wvSpdRt  = 128.f;
    m_wavePlayerWrapper.SetConfig(config);
    m_wavePlayerWrapper.SetBoxes({4.f, 4.f}, {2.f, 2.f});
    m_wavePlayerWrapper.SetPosition(sf::Vector2f(m_boxPosition.x + 550.f,
                                                 m_boxPosition.y));
    m_wavePlayerWrapper.Init();
    PulsePlayerWrapper::config config2;
    config2.rows         = m_matrixHeight;
    config2.cols         = m_matrixWidth;
    config2.hiLight      = Light(125, 125, 0);
    config2.lowLight     = Light(0, 0, 0);
    config2.defaultColor = Light(255, 0, 0);
    config2.W_pulse      = 12.f;
    config2.repeat       = true;
    config2.speed        = 1.f;
    config2.boxSize      = m_boxSize;
    config2.boxSpacing   = m_boxSpacing;
    config2.T_repeat     = 1.f;
    m_pulsePlayerWrapper.SetPosition({
                                         m_boxPosition.x,
                                         m_boxPosition.y + 300.f
                                     });
    m_pulsePlayerWrapper.SetConfig(config2);
    m_pulsePlayerWrapper.Init();

    m_dataPlayerWrapper.SetSize(sf::Vector2f(200.f, 200.f));
    m_dataPlayerWrapper.SetPosition(sf::Vector2f(m_boxPosition.x,
                                                 m_boxPosition.y + 500.f));
    m_dataPlayerWrapper.Init();
    m_dataPlayerWrapper.Tick(0.0);
}

void LightMeUpLevel::AssignRandomColors() {
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    for (auto &light: m_lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
    }
}
