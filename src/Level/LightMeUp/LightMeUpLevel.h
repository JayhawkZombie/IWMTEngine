//
// Created by Kurt Slagle on 3/23/25.
//

#pragma once

#include "Level/Level.h"
#include "LightVisual.h"

class LightMeUpLevel : public Level
{

    void ResetAndResizeLights(size_t size, float posX, float posY, float dPosX, float dPosY, const sf::Vector2f &boxSize);
  public:

    int m_matrixHeight = 8;
    std::vector<Light> m_lights;
    LightVisual m_visual;
    /*
    virtual ~Level();

    virtual void Init();
    virtual void Destroy();
    virtual void Render(sf::RenderTarget &target);
    virtual void Tick(double delta);

    void RenderLevelEditor();
    virtual void RenderEditor();
    bool IsInitialized();
     */
    LightMeUpLevel();
    ~LightMeUpLevel() override = default;
    void Init() override;
    void Destroy() override;
    void Tick(double delta) override;
    void Render(sf::RenderTarget &target) override;

    void RenderEditor() override;
    void RenderLightsEditor();
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(LightMeUpLevel)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_visual, "visual")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_matrixHeight, "height")
RENGINE_REFLECT_CLASS_END(LightMeUpLevel)
