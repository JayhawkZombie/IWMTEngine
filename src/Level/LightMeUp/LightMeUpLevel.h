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

    using light_vector = std::vector<Light>;

    std::vector<light_vector> m_lightStates;
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
    bool RenderLightsEditor();
    bool RenderLightStatesSelectorEditor();

    size_t m_editorSelectedStateIndex = 0;
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(LightMeUpLevel)
RENGINE_REFLECT_BASE_CLASS(Level)
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_visual, "visual")
RENGINE_REFLECT_CLASS_MEMBER(LightMeUpLevel, m_matrixHeight, "height")
RENGINE_REFLECT_CLASS_END(LightMeUpLevel)
