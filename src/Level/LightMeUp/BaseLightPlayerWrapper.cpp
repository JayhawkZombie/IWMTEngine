//
// Created by Kurt Slagle on 4/21/25.
//

#include "BaseLightPlayerWrapper.h"
#include "Globals.h"
#include <Console/EngineConsole.h>

void BaseLightPlayerWrapper::Tick(double delta) {
    GameObject::Tick(delta);
    if (!m_init) {
        return;
    }
    m_visual.update();
}

bool BaseLightPlayerWrapper::ResizeNumLights(size_t numLights, Light color) {
    m_lights.resize(numLights, color);
    return m_lights.size() == numLights;
}

bool BaseLightPlayerWrapper::RenderEditor() {
    return GameObject::RenderEditor();
}

void BaseLightPlayerWrapper::GenerateCode() {
    // Generates code for the lights array
    GlobalConsole->Debug("%lu Lights", m_lights.size());
    for (size_t i = 0; i < m_lights.size(); i++) {
        GlobalConsole->Debug("arr[%lu] = CRGB(%i, %i, %i);", i, m_lights[i].r, m_lights[i].g, m_lights[i].b);
    }
}


void BaseLightPlayerWrapper::Init() {
    GameObject::Init();
}

void BaseLightPlayerWrapper::Render(sf::RenderTarget &target) {
    if (!HasInit()) {
        return;
    }
    GameObject::Render(target);
    m_visual.draw(target);
}
