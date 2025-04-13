//
// Created by Kurt Slagle on 4/11/25.
//

#include "PatternPlayerAdapter.h"

PatternPlayerAdapter::PatternPlayerAdapter() {
}

PatternPlayerAdapter::~PatternPlayerAdapter() {
}

void PatternPlayerAdapter::Tick(double delta) {
    GameObject::Tick(delta);
    m_lightPlayer2.update();
    m_visual.update();
}

void PatternPlayerAdapter::Init() {
    GameObject::Init();
    m_lights.resize(m_matrixWidth * m_matrixHeight, Light(125, 125, 125));
    m_visual.init(m_lights[0],
                  m_matrixHeight,
                  m_matrixWidth,
                  GetPosition().x,
                  GetPosition().y,
                  m_boxSpacing.x,
                  m_boxSpacing.y,
                  m_boxSize);
    m_lightPlayer2.init(m_lights[0],
                        m_matrixHeight,
                        m_matrixWidth,
                        m_patternData[0],
                        static_cast<unsigned int>(m_patternData.size()));
    m_lightPlayer2.onLt  = Light(0, 255, 255);
    m_lightPlayer2.offLt = Light(255, 0, 255);
    m_lightPlayer2.update();
    m_visual.update();
}

void PatternPlayerAdapter::Render(sf::RenderWindow &window) {
    // GameObject::Render(window);
    const auto pos = GetPosition();
    const auto size = GetSize();
    m_visual.draw(window);
}
