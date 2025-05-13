//
// Created by Kurt Slagle on 4/25/25.
//

#include "PulsePlayerWrapper.h"

#include <Editor/ImGuiHelpers.h>

PulsePlayerWrapper::~PulsePlayerWrapper() {
}

void PulsePlayerWrapper::SetConfig(const config &config) {
    m_config = config;
}

void PulsePlayerWrapper::Tick(double delta) {
    BaseLightPlayerWrapper::Tick(delta);
    m_pulsePlayer.update(static_cast<float>(delta));
}

void PulsePlayerWrapper::Init() {
    BaseLightPlayerWrapper::Init();
    ResizeNumLights(m_config.rows * m_config.cols, m_config.defaultColor);
    const auto pos = GetPosition();
    m_visual.init(GetLights()[0],
                  m_config.rows,
                  m_config.cols,
                  pos.x,
                  pos.y,
                  m_config.boxSpacing.x,
                  m_config.boxSpacing.y,
                  m_config.boxSize);
    m_visual.update();
    m_pulsePlayer.init(GetLights()[0],
                       m_config.rows,
                       m_config.cols,
                       m_config.hiLight,
                       m_config.lowLight,
                       m_config.W_pulse,
                       m_config.speed,
                       m_config.T_repeat,
                       m_config.repeat);
    SetHasInit(true);
}

void PulsePlayerWrapper::Render(sf::RenderTarget &target) {
    BaseLightPlayerWrapper::Render(target);
}

bool PulsePlayerWrapper::RenderEditor() {
    bool edited = false;
    edited      = EditorLight(m_config.lowLight, "Lo light");
    ImGui::SameLine();
    edited = edited || EditorLight(m_config.hiLight, "Hi light");
    edited = edited || EditorBoolean("Repeat", m_config.repeat);
    if (ImGui::SliderInt("W", &m_config.W_pulse, 0, 100)) {
        edited = true;
    }
    if (ImGui::SliderFloat("Speed", &m_config.speed, 0.f, 100.f, "%.3f")) {
        edited = true;
    }

    if (ImGui::SliderFloat("tRepeat", &m_config.T_repeat, 0.1f, 10.f)) {
        edited = true;
    }
    EditorViewFloat("tElap", m_pulsePlayer.tElap, ImColor(0, 255, 255, 255));
    if (edited) {
        Init();
    }
    return edited;
}

#include <fmt/ostream.h>

void PulsePlayerWrapper::GenerateCode() {
    // BaseLightPlayerWrapper::GenerateCode();
    std::ofstream file("pulsedata.pulse");
    if (!file) {
        GlobalConsole->Error("Could not open file for writing %s", "pulsedata.pulse");
        return;
    }

    fmt::println(file, "void initPulseData(PulsePlayer *pl, Light *arr) {{");
    fmt::println(file, "int rows = {}, cols = {};", m_config.rows, m_config.cols);
    fmt::println(file, "Light hiLight = {}, lowLight = {}", m_config.hiLight, m_config.lowLight);
    fmt::println(file, "int W_pulse = {};", m_config.W_pulse);
    fmt::println(file, "float speed = {}, T_repeat = {};", m_config.speed, m_config.T_repeat);
    fmt::println(file, "bool repeat = {}", m_config.repeat);
    fmt::println(file, "pl->init(arr[0], rows, cols, hiLight, lowLight, W_pulse, speed, T_repeat, repeat);");
    fmt::println(file, "}}");
}
