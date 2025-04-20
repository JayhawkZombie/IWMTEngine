//
// Created by Kurt Slagle on 4/20/25.
//

#pragma once

#include <Engine/GameObject.h>
#include "./Light_types/DataPlayer.h"
#include "LightVisual.h"

class DataPlayerWrapper : public GameObject {
public:

    ~DataPlayerWrapper() override;

    virtual void Tick(double delta) override;
    virtual void Init() override;
    virtual void Render(sf::RenderTarget &target) override;

    std::vector<Light>& GetLights() {
        return m_dataPlayerLights;
    }

    bool m_init = false;
    sf::Vector2f m_boxSize = sf::Vector2f(8.f, 8.f);
    sf::Vector2f m_boxSpacing = sf::Vector2f(4.f, 4.f);
    DataPlayer m_dataPlayer;
    LightVisual m_dataPlayerVisual;
    std::vector<uint8_t> m_dataPlayerDataVector;
    std::vector<Light> m_dataPlayerLights;

};
