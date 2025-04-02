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
    void setPattern(LightPatterns::PatternType type, unsigned int stepPause = 1, unsigned int param = 0);
    void addPattern(LightPatterns::PatternType type, unsigned int stepPause = 1, unsigned int param = 0);
    void clearPatterns();
    
    // Pattern sequence control
    void nextPattern();
    void previousPattern();
    size_t getCurrentPatternIndex() const { return m_currentPatternIndex; }
    size_t getPatternCount() const { return m_patterns.size(); }
    void removePattern(size_t index);
    void movePatternUp(size_t index);
    void movePatternDown(size_t index);
    const patternData& getPattern(size_t index) const { return m_patterns[index]; }
    
    // Color control
    void setOnColor(const Light& color) { m_onColor = color; }
    void setOffColor(const Light& color) { m_offColor = color; }
    
    // Speed control
    void setSpeed(float speed);
    
    // Pattern state info
    unsigned int getCurrentStep() const { return m_player->stepIter; }
    unsigned int getPatternLength() const { return m_player->getPattLength(); }
    
// private:
    std::vector<Light>& m_lights;  // Reference to external light states
    std::vector<patternData> m_patterns;  // Pattern sequence
    std::unique_ptr<LightPlayer2> m_player;  // Pattern player
    Light m_onColor{255, 255, 255};  // Color for 'on' state
    Light m_offColor{0, 0, 0};      // Color for 'off' state
    double m_accumulator{0.0};      // Time accumulator for updates
    float m_speed{1.0f};           // Pattern playback speed multiplier
    size_t m_rows{8};             // Number of rows in the LED matrix
    size_t m_cols{8};             // Number of columns in the LED matrix
    size_t m_currentPatternIndex{0};  // Current pattern in the sequence
}; 

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(PatternPlayer)
// RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_lights, "lights")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_patterns, "patterns")
// RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_player, "player")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_onColor, "on_color")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_offColor, "off_color")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_accumulator, "accumulator")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_speed, "speed")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_rows, "rows")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_cols, "cols")
RENGINE_REFLECT_CLASS_MEMBER(PatternPlayer, m_currentPatternIndex, "current_pattern_index")
RENGINE_REFLECT_CLASS_END(PatternPlayer)
