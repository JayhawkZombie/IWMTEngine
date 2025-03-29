#include "PatternPlayer.h"

PatternPlayer::PatternPlayer(size_t rows, size_t cols) {
    // Initialize lights
    m_lights.resize(rows * cols);
    for (auto& light : m_lights) {
        light.init(0, 0, 0);
        light.updateFloatsFromRGB();
    }
    
    // Initialize pattern player
    m_player = std::make_unique<LightPlayer2>();
    
    // Add a default pattern (all off)
    m_patterns.push_back(patternData());
    m_patterns.back().init(0, 1, 0);
    
    // Initialize the player with our lights
    m_player->init(m_lights[0], rows, cols, m_patterns[0], 1);
}

void PatternPlayer::update(double deltaTime) {
    // Accumulate time until we reach 100ms (10fps for pattern updates)
    m_accumulator += deltaTime;
    if (m_accumulator < 0.1) {
        return;
    }
    m_accumulator = 0;
    
    // Update pattern state
    m_player->update(m_onColor, m_offColor);
    
    // Update ImGui colors
    for (auto& light : m_lights) {
        light.updateFloatsFromRGB();
    }
}

void PatternPlayer::setPattern(unsigned int funcIndex, unsigned int stepPause, unsigned int param) {
    clearPatterns();
    addPattern(funcIndex, stepPause, param);
}

void PatternPlayer::addPattern(unsigned int funcIndex, unsigned int stepPause, unsigned int param) {
    m_patterns.push_back(patternData());
    m_patterns.back().init(funcIndex, stepPause, param);
    m_player->init(m_lights[0], m_lights.size() / 8, 8, m_patterns[0], m_patterns.size());
}

void PatternPlayer::clearPatterns() {
    m_patterns.clear();
    m_patterns.push_back(patternData());  // Add default "all off" pattern
    m_patterns.back().init(0, 1, 0);
    m_player->init(m_lights[0], m_lights.size() / 8, 8, m_patterns[0], 1);
} 