//
// Created by Kurt Slagle on 3/23/25.
//

#pragma once

#include "Level/Level.h"
#include "LightVisual.h"
#include "StarrySky.h"
#include "Light_types/LightPlayer2.h"
// #include "Light_types/PulsePlayer.h"

#include "WavePlayerWrapper.h"
#include "DataPlayerWrapper.h"
#include "PulsePlayerWrapper.h"
#include <random>
#include <cereal/types/polymorphic.hpp>

class LightMeUpLevel : public Level
{
    void ResetAndResizeLights();
    void AssignRandomColors();

  public:
    using light_vector = std::vector<Light>;

    int m_matrixHeight = 8;
    int m_matrixWidth = 8;
    Light m_backgroundColor = Light(0, 0, 0);
    LightPlayer2 m_lightPlayer2;
    LightVisual m_visual;
    std::vector<patternData> m_patternData;

    DataPlayerWrapper m_dataPlayerWrapper;
    WavePlayerWrapper m_wavePlayerWrapper;
    PulsePlayerWrapper m_pulsePlayerWrapper;

    sf::Vector2f m_boxSize{16.f, 16.f};
    sf::Vector2f m_boxSpacing{4.f, 4.f};
    sf::Vector2f m_boxPosition{400.f, 300.f};

    light_vector m_lights;
    StarrySky m_starrySky;
    std::mt19937 m_rng;  // Random number generator for colors

    float C_Rt[3] = {3, 2, 1};

    LightMeUpLevel();
    ~LightMeUpLevel() override = default;
    void Init() override;
    void InitPatterns();
    // void InitDataPlayer();
    void Destroy() override;
    void Tick(double delta) override;
    void Render(sf::RenderTarget &target) override;

    void UpdateVisuals(double delta);
    void RenderVisuals(sf::RenderTarget &target);

    sf::Vector2f GetLEDsPosition() const;
    void SetLEDsPosition(const sf::Vector2f &pos);

    bool RenderEditor() override;
    bool RenderLightsEditor();
    bool RenderPatternPlayerEditorTab();
    bool RenderWavePlayerEditorTab();
    bool RenderPulsePlayerEditorTab();
    bool RenderDataPlayerEditorTab();
};

// Register DerivedClassOne
CEREAL_REGISTER_TYPE(LightMeUpLevel)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Level, LightMeUpLevel)

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(LightMeUpLevel)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_matrixWidth, "width")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_matrixHeight, "height")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_boxSize, "boxSize")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_boxSpacing, "boxSpacing")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_boxPosition, "boxPosition")
RENGINE_REFLECT_CLASS_END(LightMeUpLevel)
