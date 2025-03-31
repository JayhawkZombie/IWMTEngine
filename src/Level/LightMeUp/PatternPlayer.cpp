#include "PatternPlayer.h"

PatternPlayer::PatternPlayer(std::vector<Light>& lights, size_t rows, size_t cols)
    : m_lights(lights)  // Initialize reference to external lights
    , m_rows(rows)      // Store the matrix dimensions
    , m_cols(cols)
{
    // Initialize pattern player
    m_player = std::make_unique<LightPlayer2>();
    
    // Add a default pattern (all off)
    m_patterns.push_back(patternData());
    m_patterns.back().init(0, 1, 0);
    
    // Initialize the player with our lights
    m_player->init(m_lights, m_rows, m_cols, m_patterns[0], 1);
}

void PatternPlayer::update(double deltaTime) {
    // Accumulate time until we reach the update interval (scaled by speed)
    m_accumulator += deltaTime;
    
    // Calculate how many updates to perform based on speed
    double targetTime = 0.016 / m_speed;  // Adjust target time based on speed
    if (m_accumulator < targetTime) {
        return;
    }
    
    // Calculate number of updates to perform
    int updates = static_cast<int>(m_accumulator / targetTime);
    m_accumulator -= updates * targetTime;
    
    // Perform multiple updates if speed is high
    for (int i = 0; i < updates; i++) {
        // Update pattern state
        m_player->update(m_onColor, m_offColor);
    }
    
    // Update ImGui colors for all lights
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
    // Initialize with the current pattern and only one pattern
    m_player->init(m_lights, m_rows, m_cols, m_patterns.back(), 1);
}

void PatternPlayer::clearPatterns() {
    m_patterns.clear();
    m_patterns.push_back(patternData());  // Add default "all off" pattern
    m_patterns.back().init(0, 1, 0);
    // Initialize with the default pattern and only one pattern
    m_player->init(m_lights, m_rows, m_cols, m_patterns.back(), 1);
}

void PatternPlayer::setSpeed(float speed) {
    m_speed = std::max(0.1f, speed);  // Ensure speed is at least 0.1
} 
