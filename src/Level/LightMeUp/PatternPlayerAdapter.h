//
// Created by Kurt Slagle on 4/11/25.
//

#pragma once

#include <Engine/GameObject.h>

#include "LightVisual.h"
#include "Light_types/LightPlayer2.h"

class PatternPlayerAdapter : public GameObject {
public:

    PatternPlayerAdapter();
    ~PatternPlayerAdapter() override;

    // LightPlayer2 IS the pattern player type
    // So we need the player type, the pattern data,
    // the lights to operate on, and a visual
    // to display it, yikes
    LightPlayer2 m_lightPlayer2;
    std::vector<patternData> m_patternData;
    std::vector<Light> m_lights;
    LightVisual m_visual;

    sf::Vector2f m_boxSize{16.f, 16.f};
    sf::Vector2f m_boxSpacing{4.f, 4.f};
    int m_matrixHeight = 8;
    int m_matrixWidth = 8;

    void Tick(double delta) override;
    void Init() override;
    void Render(sf::RenderWindow &window) override;

};
