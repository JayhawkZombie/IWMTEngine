//
// Created by Kurt Slagle on 4/21/25.
//

#pragma once

#include <Engine/GameObject.h>

#include "LightVisual.h"
#include "Light_types/Light.h"


class BaseLightPlayerWrapper : public GameObject {
public:
    BaseLightPlayerWrapper()                   = default;
    virtual ~BaseLightPlayerWrapper() override = default;

    virtual void Tick(double delta) override;
    virtual void Init() override;
    virtual void Render(sf::RenderTarget &target) override;

    std::vector<Light> &GetLights() {
        return m_lights;
    }

    LightVisual &GetLightVisual() { return m_visual; }

    bool ResizeNumLights(size_t numLights, Light color);

    bool HasInit() const { return m_init; }

    void SetHasInit(bool hasInit) { m_init = hasInit; }

    virtual bool RenderEditor() override;
    virtual bool SaveConfig(const std::string &filename);
    virtual bool LoadConfig(const std::string &filename);

    virtual void GenerateCode();

protected:
    LightVisual m_visual;

private:
    bool m_init               = false;
    sf::Vector2f m_boxSize    = sf::Vector2f(8.f, 8.f);
    sf::Vector2f m_boxSpacing = sf::Vector2f(4.f, 4.f);
    std::vector<Light> m_lights;
};
