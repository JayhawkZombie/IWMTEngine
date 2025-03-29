#pragma once

#include "Light.h"
#include "ArduinoSim/src/LightPlayer2.h"
#include <vector>
#include <memory>

class PatternPlayer {
public:
    PatternPlayer(std::vector<Light>& lights, size_t rows = 8, size_t cols = 8);
    
    // Update pattern state
    void update(double deltaTime);
    
    // Get current light states
    const std::vector<Light>& getLights() const { return m_lights; }
    
    // Pattern control
    void setPattern(unsigned int funcIndex, unsigned int stepPause = 1, unsigned int param = 0);
    void addPattern(unsigned int funcIndex, unsigned int stepPause = 1, unsigned int param = 0);
    void clearPatterns();
    
    // Color control
    void setOnColor(const Light& color) { m_onColor = color; }
    void setOffColor(const Light& color) { m_offColor = color; }
    
    // Speed control
    void setSpeed(float speed);
    
    // Pattern state info
    unsigned int getCurrentStep() const { return m_player->stepIter; }
    unsigned int getPatternLength() const { return m_player->getPattLength(); }
    
private:
    std::vector<Light>& m_lights;  // Reference to external light states
    std::vector<patternData> m_patterns;  // Pattern sequence
    std::unique_ptr<LightPlayer2> m_player;  // Pattern player
    Light m_onColor{255, 255, 255};  // Color for 'on' state
    Light m_offColor{0, 0, 0};      // Color for 'off' state
    double m_accumulator{0.0};      // Time accumulator for updates
    float m_speed{1.0f};           // Pattern playback speed multiplier
}; 