#pragma once

#include <string>
#include <array>
#include <vector>

namespace LightPatterns {

enum class PatternType {
    AllOff = 0,
    ScrollRight = 1,
    ScrollLeft = 2,
    FillFromRight = 3,
    FillFromLeft = 4,
    CrissCross = 5,
    AlternateBlink = 6,
    CheckerBlink = 7,
    ScrollColumnRight = 10,
    ScrollColumnLeft = 11,
    ScrollRowBottom = 12,
    ScrollRowTop = 13,
    ScrollBoxIn = 14,
    ScrollBoxOut = 15,
    ScrollDiagonal = 16,
    CustomBitPattern = 100
};

enum class PatternCategory {
    Basic,      // Simple patterns like all off
    Linear,     // Patterns that work on linear LED array
    Grid,       // Patterns that work on 2D grid
    Special     // Special patterns like custom bit patterns
};

struct PatternConfig {
    PatternType type;
    std::string name;
    PatternCategory category;
    unsigned int defaultStepPause;
    unsigned int defaultParam;
    std::string description;
};

// Define all available patterns
inline const std::vector<PatternConfig> AllPatterns = {
    {PatternType::AllOff, "All Off", PatternCategory::Basic, 1, 0, "Turn all LEDs off"},
    {PatternType::ScrollRight, "Scroll Right", PatternCategory::Linear, 1, 3, "Scroll a group of LEDs from left to right"},
    {PatternType::ScrollLeft, "Scroll Left", PatternCategory::Linear, 1, 3, "Scroll a group of LEDs from right to left"},
    {PatternType::FillFromRight, "Fill From Right", PatternCategory::Linear, 2, 1, "Fill LEDs from right to left"},
    {PatternType::FillFromLeft, "Fill From Left", PatternCategory::Linear, 2, 1, "Fill LEDs from left to right"},
    {PatternType::CrissCross, "Criss Cross", PatternCategory::Linear, 1, 3, "Cross-moving LED groups"},
    {PatternType::AlternateBlink, "Alternate Blink", PatternCategory::Linear, 5, 1, "Alternating blinking pattern"},
    {PatternType::CheckerBlink, "Checker Blink", PatternCategory::Grid, 8, 10, "Checkerboard blinking pattern"},
    {PatternType::ScrollColumnRight, "Scroll Column Right", PatternCategory::Grid, 2, 1, "Scroll a column from left to right"},
    {PatternType::ScrollColumnLeft, "Scroll Column Left", PatternCategory::Grid, 2, 1, "Scroll a column from right to left"},
    {PatternType::ScrollRowBottom, "Scroll Row Bottom", PatternCategory::Grid, 2, 1, "Scroll a row from top to bottom"},
    {PatternType::ScrollRowTop, "Scroll Row Top", PatternCategory::Grid, 2, 1, "Scroll a row from bottom to top"},
    {PatternType::ScrollBoxIn, "Scroll Box In", PatternCategory::Grid, 4, 1, "Animate box pattern inward"},
    {PatternType::ScrollBoxOut, "Scroll Box Out", PatternCategory::Grid, 4, 1, "Animate box pattern outward"},
    {PatternType::ScrollDiagonal, "Scroll Diagonal", PatternCategory::Grid, 2, 1, "Diagonal scrolling pattern"},
    {PatternType::CustomBitPattern, "Custom Bit Pattern", PatternCategory::Special, 20, 1, "Custom pattern defined by bit array"}
};

// Helper functions
inline const PatternConfig& GetPatternConfig(PatternType type) {
    auto it = std::find_if(AllPatterns.begin(), AllPatterns.end(),
        [type](const PatternConfig& config) { return config.type == type; });
    return *it;  // Note: Assumes pattern type exists in AllPatterns
}

inline std::vector<PatternConfig> GetPatternsByCategory(PatternCategory category) {
    std::vector<PatternConfig> result;
    std::copy_if(AllPatterns.begin(), AllPatterns.end(), std::back_inserter(result),
        [category](const PatternConfig& config) { return config.category == category; });
    return result;
}

} // namespace LightPatterns 