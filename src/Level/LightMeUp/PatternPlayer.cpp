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
    m_patterns.back().init(LightPatterns::PatternType::AllOff, 1, 0);
    
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
        
        // For bit patterns, we want to display them for their full step pause duration
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            // Only move to next pattern after step pause ticks
            if (m_player->stepTimer >= m_patterns[m_currentPatternIndex].stepPause - 1) {
                m_player->stepTimer = 0;
                nextPattern();
            }
        } else {
            // For other patterns, check if current pattern is complete and move to next pattern
            unsigned int currentLength = m_player->getPattLength();
            if (m_player->stepIter >= currentLength) {
                m_player->stepIter = 0;  // Reset step counter
                nextPattern();
            }
        }
    }
    
    // Update ImGui colors for all lights
    for (auto& light : m_lights) {
        light.updateFloatsFromRGB();
    }
}

void PatternPlayer::setPattern(LightPatterns::PatternType type, unsigned int stepPause, unsigned int param) {
    clearPatterns();
    addPattern(type, stepPause, param);
}

void PatternPlayer::addPattern(LightPatterns::PatternType type, unsigned int stepPause, unsigned int param) {
    size_t newPatternIndex = m_patterns.size();
    m_patterns.push_back(patternData());
    m_patterns.back().init(type, stepPause, param);
    m_currentPatternIndex = newPatternIndex;  // Switch to the new pattern
    
    // Reset accumulator when adding a new pattern
    m_accumulator = 0.0;
    
    // Initialize with the new pattern
    m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
}

void PatternPlayer::clearPatterns() {
    m_patterns.clear();
    m_patternStateData.clear();  // Clear all stored state data
    m_patterns.push_back(patternData());  // Add default "all off" pattern
    m_patterns.back().init(LightPatterns::PatternType::AllOff, 1, 0);
    m_currentPatternIndex = 0;
    // Initialize with the default pattern
    m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], 1);
}

void PatternPlayer::nextPattern() {
    if (m_patterns.size() > 1) {
        m_currentPatternIndex = (m_currentPatternIndex + 1) % m_patterns.size();
        
        // Reset step counter when switching patterns
        m_player->stepIter = 0;
        
        // If this is a custom bit pattern, make sure to set its state data
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            auto it = m_patternStateData.find(m_currentPatternIndex);
            if (it != m_patternStateData.end()) {
                m_player->setStateData(it->second.data(), it->second.size());
            }
        }
        
        m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
    }
}

void PatternPlayer::previousPattern() {
    if (m_patterns.size() > 1) {
        m_currentPatternIndex = (m_currentPatternIndex == 0) ? m_patterns.size() - 1 : m_currentPatternIndex - 1;
        
        // Reset step counter when switching patterns
        m_player->stepIter = 0;
        
        // If this is a custom bit pattern, make sure to set its state data
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            auto it = m_patternStateData.find(m_currentPatternIndex);
            if (it != m_patternStateData.end()) {
                m_player->setStateData(it->second.data(), it->second.size());
            }
        }
        
        m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
    }
}

void PatternPlayer::removePattern(size_t index) {
    if (index < m_patterns.size() && m_patterns.size() > 1) {
        // Remove the pattern's state data if it exists
        m_patternStateData.erase(index);
        
        // Shift all state data indices above this one down by 1
        for (size_t i = index + 1; i < m_patterns.size(); i++) {
            auto it = m_patternStateData.find(i);
            if (it != m_patternStateData.end()) {
                m_patternStateData[i - 1] = std::move(it->second);
                m_patternStateData.erase(i);
            }
        }
        
        m_patterns.erase(m_patterns.begin() + index);
        if (m_currentPatternIndex >= m_patterns.size()) {
            m_currentPatternIndex = m_patterns.size() - 1;
        }
        
        // If current pattern is a bit pattern, set its state data
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            auto it = m_patternStateData.find(m_currentPatternIndex);
            if (it != m_patternStateData.end()) {
                m_player->setStateData(it->second.data(), it->second.size());
            }
        }
        
        m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
    }
}

void PatternPlayer::movePatternUp(size_t index) {
    if (index > 0 && index < m_patterns.size()) {
        // Swap patterns
        std::swap(m_patterns[index], m_patterns[index - 1]);
        
        // Swap state data if either pattern is a bit pattern
        auto it1 = m_patternStateData.find(index);
        auto it2 = m_patternStateData.find(index - 1);
        if (it1 != m_patternStateData.end() && it2 != m_patternStateData.end()) {
            std::swap(it1->second, it2->second);
        } else if (it1 != m_patternStateData.end()) {
            m_patternStateData[index - 1] = std::move(it1->second);
            m_patternStateData.erase(index);
        } else if (it2 != m_patternStateData.end()) {
            m_patternStateData[index] = std::move(it2->second);
            m_patternStateData.erase(index - 1);
        }
        
        if (m_currentPatternIndex == index) {
            m_currentPatternIndex--;
        } else if (m_currentPatternIndex == index - 1) {
            m_currentPatternIndex++;
        }
        
        // If current pattern is a bit pattern, set its state data
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            auto it = m_patternStateData.find(m_currentPatternIndex);
            if (it != m_patternStateData.end()) {
                m_player->setStateData(it->second.data(), it->second.size());
            }
        }
        
        m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
    }
}

void PatternPlayer::movePatternDown(size_t index) {
    if (index < m_patterns.size() - 1) {
        // Swap patterns
        std::swap(m_patterns[index], m_patterns[index + 1]);
        
        // Swap state data if either pattern is a bit pattern
        auto it1 = m_patternStateData.find(index);
        auto it2 = m_patternStateData.find(index + 1);
        if (it1 != m_patternStateData.end() && it2 != m_patternStateData.end()) {
            std::swap(it1->second, it2->second);
        } else if (it1 != m_patternStateData.end()) {
            m_patternStateData[index + 1] = std::move(it1->second);
            m_patternStateData.erase(index);
        } else if (it2 != m_patternStateData.end()) {
            m_patternStateData[index] = std::move(it2->second);
            m_patternStateData.erase(index + 1);
        }
        
        if (m_currentPatternIndex == index) {
            m_currentPatternIndex++;
        } else if (m_currentPatternIndex == index + 1) {
            m_currentPatternIndex--;
        }
        
        // If current pattern is a bit pattern, set its state data
        if (m_patterns[m_currentPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
            auto it = m_patternStateData.find(m_currentPatternIndex);
            if (it != m_patternStateData.end()) {
                m_player->setStateData(it->second.data(), it->second.size());
            }
        }
        
        m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
    }
}

void PatternPlayer::setSpeed(float speed) {
    m_speed = std::max(0.1f, speed);  // Ensure speed is at least 0.1
}

void PatternPlayer::setCustomBitPattern(const std::vector<uint8_t>& stateData, unsigned int stepPause) {
    clearPatterns();
    addCustomBitPattern(stateData, stepPause);
}

void PatternPlayer::addCustomBitPattern(const std::vector<uint8_t>& stateData, unsigned int stepPause) {
    // Add the new pattern
    size_t newPatternIndex = m_patterns.size();
    m_patterns.push_back(patternData());
    m_patterns.back().init(LightPatterns::PatternType::CustomBitPattern, stepPause, 1);
    
    // Store the state data for this pattern
    m_patternStateData[newPatternIndex] = stateData;
    
    // Switch to the new pattern
    m_currentPatternIndex = newPatternIndex;
    
    // Set the state data and initialize with the new pattern
    m_player->setStateData(m_patternStateData[newPatternIndex].data(), m_patternStateData[newPatternIndex].size());
    m_player->init(m_lights, m_rows, m_cols, m_patterns[m_currentPatternIndex], m_patterns.size());
} 
