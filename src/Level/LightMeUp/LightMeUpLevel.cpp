//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <Globals.h>
#include <imgui.h>
#include <fmt/base.h>
#include <random>

// Define predefined bit patterns
const std::vector<std::pair<const char*, std::vector<uint8_t>>> LightMeUpLevel::PREDEFINED_BIT_PATTERNS = {
    {"Box Pattern", {
        0b00111100,  // Row 1
        0b00100100,  // Row 2
        0b00100100,  // Row 3
        0b00100100,  // Row 4
        0b00100100,  // Row 5
        0b00100100,  // Row 6
        0b00100100,  // Row 7
        0b00111100   // Row 8
    }},
    {"Centered Box", {
        0b00000000,  // Row 1
        0b00000000,  // Row 2
        0b00111100,  // Row 3
        0b00111100,  // Row 4
        0b00111100,  // Row 5
        0b00111100,  // Row 6
        0b00000000,  // Row 7
        0b00000000   // Row 8
    }},
    {"Wide Rectangle", {
        0b00000000,  // Row 1
        0b00000000,  // Row 2
        0b11111111,  // Row 3
        0b10000001,  // Row 4
        0b10000001,  // Row 5
        0b11111111,  // Row 6
        0b00000000,  // Row 7
        0b00000000   // Row 8
    }}
};

LightMeUpLevel::LightMeUpLevel() 
    : m_starrySky(15)  // Initialize with 15 stars per cell
    , m_rng(std::random_device()())  // Initialize RNG with random seed
{
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    m_lights.resize(64);
    for (auto& light : m_lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
        light.updateFloatsFromRGB();  // Update the float values for ImGui
    }
    const auto pos = GetLEDsPosition();
    m_visual.init(m_lights.data(),
                  8,
                  8,
                  pos.x,
                  pos.y,
                  8.f,
                  8.f,
                  sf::Vector2f(32, 32));
    
    // Initialize pattern player with our LED vector
    m_patternPlayer = std::make_unique<PatternPlayer>(m_lights, 8, 8);
}

void LightMeUpLevel::Init() {
    Level::Init();
    fmt::println("LightMeUpLevel::Init");
    m_lights.resize(m_matrixHeight * m_matrixHeight);
    
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    for (auto& light: m_lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
        light.updateFloatsFromRGB();  // Update the float values for ImGui
    }
    const auto pos = GetLEDsPosition();
    m_visual.init(m_lights.data(), 8, 8, pos.x, pos.y, 8, 8, sf::Vector2f(32, 32));
    m_visual.update();
    
    // Reinitialize pattern player with our LED vector
    m_patternPlayer = std::make_unique<PatternPlayer>(m_lights, 8, 8);
}

void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
    m_starrySky.update(static_cast<float>(deltaTime));
    
    // Update pattern player
    m_patternPlayer->update(deltaTime);
    
    // Update star cell visibility and color based on LED states
    for (size_t y = 0; y < 8; ++y) {
        for (size_t x = 0; x < 8; ++x) {
            // Get the LED state using the correct matrix index
            const auto& light = m_lights[y * 8 + x];
            // Calculate visibility based on average brightness
            float brightness = (light.r + light.g + light.b) / (3.0f * 255.0f);
            // Map the coordinates to the starry sky grid
            m_starrySky.setCellVisibility(x, y, brightness);
            m_starrySky.setCellColor(x, y, sf::Color(light.r, light.g, light.b));
        }
    }
    
    // Update the visual representation
    m_visual.update();
}

void LightMeUpLevel::Render(sf::RenderTarget &target) {
    // Get the bounds of the light grid
    sf::FloatRect lightBounds = m_visual.getRect();
    // Add some padding around the lights for the starry background
    lightBounds.left -= 50.f;
    lightBounds.top -= 500.f;
    lightBounds.width += 100.f;
    lightBounds.height += 100.f;
    
    // Draw starry sky with background in the light grid area
    m_starrySky.draw(target, lightBounds);
    // Then draw the light visualization on top
    m_visual.draw(target);
}

sf::Vector2f LightMeUpLevel::GetLEDsPosition() const {
    return sf::Vector2f(200.f, 600.f);
}

bool EditorVector2f(sf::Vector2f &vec,
                    const char *label,
                    float minx,
                    float miny,
                    float maxx,
                    float maxy) {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR",
                      ImVec2(0, 80),
                      ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,
                      ImGuiWindowFlags_None);
    ImGui::Indent(5.f);
    if (ImGui::DragFloat("x", &vec.x, 2.f, minx, maxx)) {
        fmt::println("Edited vector x = {}", vec.x);
        edited = true;
    }

    if (ImGui::DragFloat("y", &vec.y, 2.f, miny, maxy)) {
        fmt::println("Edited vector y = {}", vec.y);
        edited = true;
    }

    ImGui::Unindent();
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

void LightMeUpLevel::ResetAndResizeLights(size_t size,
                                          float posX,
                                          float posY,
                                          float dPosX,
                                          float dPosY,
                                          const sf::Vector2f &boxSize) {
    m_lights.resize(size, Light(125, 125, 125));
    m_visual.init(m_lights.data(),
                  m_matrixHeight,
                  m_matrixHeight,
                  posX,
                  posY,
                  dPosX,
                  dPosY,
                  boxSize);
    m_visual.update();
    
    // Reinitialize pattern player with new dimensions
    m_patternPlayer = std::make_unique<PatternPlayer>(m_lights, m_matrixHeight, m_matrixHeight);
}

void LightMeUpLevel::RenderEditor() {
    static sf::Vector2f visualBoxSize = sf::Vector2f(32, 32);

    if (ImGui::Begin(("LightMeUp"))) {
        ImGui::Text("Visual");
        ImGui::SetNextItemWidth(100.f);
        if (ImGui::DragInt("Matrix Height", &m_matrixHeight, 0.5f, 1, 18)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("Total Lights: {}", totalLights);
            ResetAndResizeLights(totalLights,
                                 50.f,
                                 50.f,
                                 8.f,
                                 8.f,
                                 visualBoxSize);
        }
        ImGui::SameLine();

        if (EditorVector2f(visualBoxSize, "Box Size", 4.f, 4.f, 150.f, 150.f)) {
            const auto totalLights = m_matrixHeight * m_matrixHeight;
            fmt::println("New vector value: {},{}",
                         visualBoxSize.x,
                         visualBoxSize.y);
            const auto pos = GetLEDsPosition();
            ResetAndResizeLights(totalLights,
                                 pos.x,
                                 pos.y,
                                 8.f,
                                 8.f,
                                 visualBoxSize);
        }
        
        // Add pattern editor UI
        RenderPatternEditor();
        
        RenderLightsEditor();
    }
    ImGui::End();
}

bool LightMeUpLevel::RenderPatternEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("PatternEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x, 300.f),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None)) {
        ImGui::Text("Pattern Control");
        ImGui::Separator();
        
        // Pattern selection
        static int selectedPatternIndex = 0;
        
        // Create category combo box
        static int selectedCategory = 0;
        const char* categories[] = {
            "Basic",
            "Linear",
            "Grid",
            "Special"
        };
        
        if (ImGui::Combo("Category", &selectedCategory, categories, IM_ARRAYSIZE(categories))) {
            // When category changes, select first pattern in that category
            auto categoryPatterns = LightPatterns::GetPatternsByCategory(
                static_cast<LightPatterns::PatternCategory>(selectedCategory));
            if (!categoryPatterns.empty()) {
                selectedPatternIndex = 0;
                edited = true;
            }
        }
        
        // Get patterns for current category
        auto categoryPatterns = LightPatterns::GetPatternsByCategory(
            static_cast<LightPatterns::PatternCategory>(selectedCategory));
        
        // Pattern selection combo
        if (!categoryPatterns.empty()) {
            std::vector<const char*> patternNames;
            for (const auto& pattern : categoryPatterns) {
                patternNames.push_back(pattern.name.c_str());
            }
            
            if (ImGui::Combo("Pattern", &selectedPatternIndex, patternNames.data(), patternNames.size())) {
                edited = true;
            }
            
            // Pattern parameters
            static int parameter = 0;
            
            if (ImGui::SliderInt("Step Pause", &m_globalStepPause, 1, 20)) {
                m_patternPlayer->setGlobalStepPause(m_globalStepPause);
                edited = true;
            }
            ImGui::SliderInt("Parameter", &parameter, 0, 20);
            
            // Add pattern button
            if (ImGui::Button("Add Pattern")) {
                // Check if this is a custom bit pattern
                if (categoryPatterns[selectedPatternIndex].type == LightPatterns::PatternType::CustomBitPattern) {
                    // Show bit pattern selector
                    ImGui::OpenPopup("Select Bit Pattern");
                } else {
                    // Use the default parameter from the pattern config
                    const auto& config = categoryPatterns[selectedPatternIndex];
                    m_patternPlayer->addPattern(config.type, m_globalStepPause, config.defaultParam);
                    edited = true;
                }
            }
            
            // Bit pattern selector popup
            if (ImGui::BeginPopup("Select Bit Pattern")) {
                ImGui::Text("Select a predefined bit pattern:");
                ImGui::Separator();
                
                for (const auto& [name, pattern] : PREDEFINED_BIT_PATTERNS) {
                    if (ImGui::Button(name)) {
                        m_patternPlayer->addCustomBitPattern(pattern, m_globalStepPause);
                        edited = true;
                        ImGui::CloseCurrentPopup();
                    }
                    
                    // Preview the pattern
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    for (size_t row = 0; row < 8; row++) {
                        for (size_t col = 0; col < 8; col++) {
                            if (col > 0) ImGui::SameLine();
                            bool isSet = (pattern[row] & (1 << (7 - col))) != 0;
                            char buttonId[32];
                            snprintf(buttonId, sizeof(buttonId), "##bit_%s_%zu_%zu", name, row, col);
                            ImGui::ColorButton(buttonId, isSet ? ImVec4(1,1,1,1) : ImVec4(0,0,0,1), 0, ImVec2(10,10));
                        }
                    }
                    ImGui::EndGroup();
                }
                
                ImGui::EndPopup();
            }
        }
        
        ImGui::Separator();
        ImGui::Text("Pattern Sequence");
        
        // Pattern sequence list
        for (size_t i = 0; i < m_patternPlayer->getPatternCount(); i++) {
            ImGui::PushID(static_cast<int>(i));
            
            const auto& pattern = m_patternPlayer->getPattern(i);
            const auto& config = LightPatterns::GetPatternConfig(pattern.type);
            
            ImGui::BeginGroup();
            if (i == m_patternPlayer->getCurrentPatternIndex()) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
            }
            
            ImGui::Text("%zu: %s", i + 1, config.name.c_str());
            
            if (i == m_patternPlayer->getCurrentPatternIndex()) {
                ImGui::PopStyleColor();
            }
            
            ImGui::SameLine();
            
            if (ImGui::Button("Up") && i > 0) {
                m_patternPlayer->movePatternUp(i);
                edited = true;
            }
            
            ImGui::SameLine();
            
            if (ImGui::Button("Down") && i < m_patternPlayer->getPatternCount() - 1) {
                m_patternPlayer->movePatternDown(i);
                edited = true;
            }
            
            ImGui::SameLine();
            
            if (ImGui::Button("Remove")) {
                m_patternPlayer->removePattern(i);
                edited = true;
            }
            
            ImGui::EndGroup();
            ImGui::PopID();
        }
        
        ImGui::Separator();
        
        // Pattern playback controls
        static float patternSpeed = 1.0f;
        if (ImGui::SliderFloat("Pattern Speed", &patternSpeed, 0.1f, 5.0f, "%.1fx")) {
            m_patternPlayer->setSpeed(patternSpeed);
            edited = true;
        }
        
        // Display current step and pattern length
        ImGui::Text("Pattern Progress: %u / %u", 
                   m_patternPlayer->getCurrentStep(),
                   m_patternPlayer->getPatternLength());
        
        // Pattern colors
        static Light onColor{255, 255, 255};
        static Light offColor{0, 0, 0};
        
        ImGui::PushID("OnColor");
        if (onColor.RenderEditor()) {
            onColor.updateRGBFromFloats();
            m_patternPlayer->setOnColor(onColor);
            edited = true;
        }
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::Text("On Color");
        
        ImGui::PushID("OffColor");
        if (offColor.RenderEditor()) {
            offColor.updateRGBFromFloats();
            m_patternPlayer->setOffColor(offColor);
            edited = true;
        }
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::Text("Off Color");
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

bool LightMeUpLevel::RenderLightsEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("LightsEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 100.f),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Individual Light Control");
        ImGui::Separator();
        
        // Add individual light controls if needed
        
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}
