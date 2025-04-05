//
// Created by Kurt Slagle on 3/23/25.
//

#pragma once

#include "Level/Level.h"
#include "LightVisual.h"
#include "StarrySky.h"
#include <random>

class LightMeUpLevel : public Level
{

    void ResetAndResizeLights(size_t size, float posX, float posY, float dPosX, float dPosY, const sf::Vector2f &boxSize);
  public:

    int m_matrixHeight = 8;

    using light_vector = std::vector<Light>;

    light_vector m_lights;
    LightVisual m_visual;
    StarrySky m_starrySky;
    std::mt19937 m_rng;  // Random number generator for colors

    LightMeUpLevel();
    ~LightMeUpLevel() override = default;
    void Init() override;
    void Destroy() override;
    void Tick(double delta) override;
    void Render(sf::RenderTarget &target) override;

    sf::Vector2f GetLEDsPosition() const;

    void RenderEditor() override;
    bool RenderLightsEditor();
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(LightMeUpLevel)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_visual, "visual")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_matrixHeight, "height")
RENGINE_REFLECT_CLASS_END(LightMeUpLevel)
