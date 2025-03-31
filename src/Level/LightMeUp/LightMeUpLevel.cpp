//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <Globals.h>
#include <imgui.h>
#include <fmt/base.h>
#include <random>

LightMeUpLevel::LightMeUpLevel() 
    : m_starrySky(15)  // Initialize with 15 stars per cell
    , m_rng(std::random_device()())  // Initialize RNG with random seed
{
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    m_lightStates.emplace_back();
    m_lightStates.front().resize(64);
    for (auto& light : m_lightStates.front()) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
        light.updateFloatsFromRGB();  // Update the float values for ImGui
    }
    const auto pos = GetLEDsPosition();
    m_visual.init(m_lightStates.front().data(),
                  8,
                  8,
                  pos.x,
                  pos.y,
                  8.f,
                  8.f,
                  sf::Vector2f(32, 32));
    
    // Initialize pattern player with our LED vector
    m_patternPlayer = std::make_unique<PatternPlayer>(m_lightStates.front(), 8, 8);
}

void LightMeUpLevel::Init() {
    Level::Init();
    fmt::println("LightMeUpLevel::Init");
    m_lightStates.emplace_back();
    auto &lights = m_lightStates.front();
    lights.resize(m_matrixHeight * m_matrixHeight);
    
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    for (auto& light: lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
        light.updateFloatsFromRGB();  // Update the float values for ImGui
    }
    const auto pos = GetLEDsPosition();
    m_visual.init(lights.data(), 8, 8, pos.x, pos.y, 8, 8, sf::Vector2f(32, 32));
    m_visual.update();
    
    // Reinitialize pattern player with our LED vector
    m_patternPlayer = std::make_unique<PatternPlayer>(lights, 8, 8);
}

void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
    m_starrySky.update(static_cast<float>(deltaTime));
    
    // Update pattern player
    m_patternPlayer->update(deltaTime);
    
    // Get the current LED states directly from the pattern player's reference
    auto& lights = m_lightStates[m_editorSelectedStateIndex];
    
    // Update star cell visibility and color based on LED states
    for (size_t y = 0; y < 8; ++y) {
        for (size_t x = 0; x < 8; ++x) {
            // Get the LED state using the correct matrix index
            const auto& light = lights[y * 8 + x];
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
    for (auto &lightVec: m_lightStates) {
        lightVec.resize(size, Light(125, 125, 125));
    }

    auto &lVec = m_lightStates[m_editorSelectedStateIndex];
    m_visual.init(lVec.data(),
                  m_matrixHeight,
                  m_matrixHeight,
                  posX,
                  posY,
                  dPosX,
                  dPosY,
                  boxSize);
    m_visual.update();
    
    // Reinitialize pattern player with new dimensions
    m_patternPlayer = std::make_unique<PatternPlayer>(lVec, m_matrixHeight, m_matrixHeight);
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
        
        RenderLightStatesSelectorEditor();
        RenderLightsEditor();
    }
    ImGui::End();
}

bool LightMeUpLevel::RenderPatternEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("PatternEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x, 200.f),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None)) {
        ImGui::Text("Pattern Control");
        ImGui::Separator();
        
        // Pattern selection
        static int currentPattern = 0;
        struct PatternOption {
            const char* name;
            int index;
        };
        
        static const PatternOption patterns[] = {
            {"All Off", 0},
            {"Scroll Right", 1},
            {"Scroll Left", 2},
            {"Fill From Right", 3},
            {"Fill From Left", 4},
            {"Criss Cross", 5},
            {"Alternate Blink", 6},
            {"Checker Blink", 7},
            {"Scroll Column Right", 10},
            {"Scroll Column Left", 11},
            {"Scroll Row Bottom", 12},
            {"Scroll Row Top", 13},
            {"Scroll Box In", 14},
            {"Scroll Box Out", 15},
            {"Scroll Diagonal", 16}
        };
        
        static int selectedPatternIndex = 0;
        if (ImGui::Combo("Pattern", &selectedPatternIndex, 
            [](void* data, int idx, const char** out_text) {
                const PatternOption* items = (const PatternOption*)data;
                if (out_text) *out_text = items[idx].name;
                return true;
            }, 
            (void*)patterns, IM_ARRAYSIZE(patterns))) 
        {
            m_patternPlayer->setPattern(patterns[selectedPatternIndex].index);
            edited = true;
        }
        
        // Pattern parameters
        static int stepPause = 1;
        static int param = 1;
        if (ImGui::SliderInt("Step Pause", &stepPause, 1, 10)) {
            m_patternPlayer->setPattern(patterns[selectedPatternIndex].index, stepPause, param);
            edited = true;
        }
        if (ImGui::SliderInt("Parameter", &param, 1, 8)) {
            m_patternPlayer->setPattern(patterns[selectedPatternIndex].index, stepPause, param);
            edited = true;
        }

        // Pattern speed control
        static float patternSpeed = 1.0f;
        if (ImGui::SliderFloat("Pattern Speed", &patternSpeed, 0.1f, 5.0f, "%.1fx")) {
            m_patternPlayer->setSpeed(patternSpeed);
            edited = true;
        }

        // Display current step and pattern length
        ImGui::Separator();
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
    if (ImGui::BeginChild("ChildLightsEditor",
                          // ImVec2(0, 0),
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 ImGui::GetContentRegionAvail().y),
                          ImGuiChildFlags_Borders |
                          ImGuiChildFlags_AlwaysAutoResize |
                          ImGuiChildFlags_AutoResizeY |
                          ImGuiChildFlags_AutoResizeX,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Light colors: ");
        ImGui::Separator();
        edited = true;
        if (m_editorSelectedStateIndex >= m_lightStates.size()) {
            // How the fuck
            GlobalConsole->
                    Error("Selected light state index out of bounds %lu/%lu",
                          m_editorSelectedStateIndex,
                          m_lightStates.size());
        } else {
            ImGui::BeginTable("Light colors",
                              8,
                              ImGuiTableFlags_Borders);
            if (m_editorSelectedStateIndex >= m_lightStates.size()) {
                ImGui::Text("Invalid light state index");
                ImGui::SameLine();
                if (ImGui::Button("Reset")) {
                    m_editorSelectedStateIndex = 0;
                }
            } else {
                light_vector &lights = m_lightStates[
                    m_editorSelectedStateIndex];

                for (auto &light: lights) {
                    ImGui::TableNextColumn();
                    if (light.RenderEditor()) {
                        light.updateRGBFromFloats();
                        m_visual.update();
                    }
                }
            }
            ImGui::EndTable();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}

bool LightMeUpLevel::RenderLightStatesSelectorEditor() {
    bool edited = false;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
    if (ImGui::BeginChild("LightStatesEditor",
                          ImVec2(ImGui::GetContentRegionAvail().x,
                                 100.f),
                          ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_None
                         )) {
        ImGui::Text("Light states");
        ImGui::Separator();
        edited = true;
        for (size_t i = 0; i < m_lightStates.size(); ++i) {
            ImGui::PushID(i);
            ImGui::PushStyleColor(ImGuiCol_Button,
                                  static_cast<ImVec4>(ImColor::HSV(i / 7.0f,
                                      0.6f,
                                      0.6f)));
            if (ImGui::Button("##button", ImVec2(50.f, 50.f))) {
                m_editorSelectedStateIndex = i;
            }
            ImGui::PopStyleColor();
            ImGui::PopID();
            ImGui::SameLine();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    return edited;
}
