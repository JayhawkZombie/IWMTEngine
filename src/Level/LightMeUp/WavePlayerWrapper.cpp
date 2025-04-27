//
// Created by Kurt Slagle on 4/21/25.
//

#include "WavePlayerWrapper.h"
#include <Logging/LogFormatting.h>
#include <Editor/ImGuiHelpers.h>
#include <fstream>
#include <Globals.h>

void WavePlayerWrapper::SetConfig(const config &config) {
    m_config = config;
}

WavePlayerWrapper::~WavePlayerWrapper() {
}

void WavePlayerWrapper::Tick(double delta) {
    BaseLightPlayerWrapper::Tick(delta);
    m_visual.update();
    m_wavePlayer.update(static_cast<float>(delta));
}

void WavePlayerWrapper::Init() {
    BaseLightPlayerWrapper::Init();
    ResizeNumLights(m_config.rows * m_config.cols, m_config.offLight);
    m_wavePlayer.init(GetLights()[0],
                      m_config.rows,
                      m_config.cols,
                      m_config.onLight,
                      m_config.offLight);
    const auto pos = GetPosition();
    m_visual.init(
                  GetLights()[0],
                  m_config.rows,
                  m_config.cols,
                  pos.x,
                  pos.y,
                  m_boxSpacing.x,
                  m_boxSpacing.y,
                  m_boxSize
                 );
    m_wavePlayer.setWaveData(m_config.AmpRt, m_config.wvLenLt, m_config.wvSpdLt, m_config.wvLenRt, m_config.wvSpdRt);
    // m_wavePlayer.setWaveData(1.f, 64.f, 64.f, 128.f, 64.f);
    m_wavePlayer.update(0.f);
    m_visual.update();
    m_wavePlayer.setSeriesCoeffs(m_config.C_Rt, 2, nullptr, 0);
    SetHasInit(true);
}

bool WavePlayerWrapper::RenderEditor() {
    bool edited = false;
    bool didSetSeries = false;
    if (ImGui::Button("Generate Code")) {
        GlobalConsole->Debug("Generating code for WavePlayer");
        GenerateCode();
    }
    edited      = EditorLight(m_config.offLight, "Lo light");
    ImGui::SameLine();
    edited = edited || EditorLight(m_config.onLight, "Hi light");
    if (ImGui::SliderFloat3("C_Rt", &m_config.C_Rt[0], 0.f, 20.f, "%.3f")) {
        didSetSeries = true;
    }
    // if (ImGui::SliderFloat("Amp Lt", &m_config.AmpLt, 0.f, 5.f, "%.3f")) {
    //     edited = true;
    // }
    if (ImGui::SliderFloat("Amp Rt", &m_config.AmpRt, 0.f, 5.f, "%.3f")) {
        edited = true;
    }

    if (ImGui::SliderFloat("WvLn Lt",
                           &m_config.wvLenLt,
                           0.f,
                           128.f,
                           "%.3f")) {
        edited = true;
                           }
    if (ImGui::SliderFloat("WvLn Rt",
                           &m_config.wvLenRt,
                           0.f,
                           128.f,
                           "%.3f")) {
        edited = true;
                           }

    if (ImGui::SliderFloat("WvSpd Lt",
                           &m_config.wvSpdLt,
                           0.f,
                           128.f,
                           "%.3f")) {
        edited = true;
                           }
    if (ImGui::SliderFloat("WvSpd Rt",
                           &m_config.wvSpdRt,
                           0.f,
                           128.f,
                           "%.3f")) {
        edited = true;
                           }

    if (edited) {
        Init();
        if (didSetSeries) {
            m_wavePlayer.setSeriesCoeffs(&m_config.C_Rt[0], 2, nullptr, 0);
        }
    }
    return edited;
}

#include <fmt/ostream.h>

void WavePlayerWrapper::GenerateCode() {
    BaseLightPlayerWrapper::GenerateCode();
    std::ofstream file("wavedata.dp");
    if (!file) {
        GlobalConsole->Error("Could not open file for wave data wavedata.dp");
        return;
    }

    fmt::println(file, "void initWaveData(WavePlayer &wp, Light *arr) {{");
    fmt::println(file, "static float C_Rt[3] = {{{},{},{}}};", m_config.C_Rt[0], m_config.C_Rt[1], m_config.C_Rt[2]);
    fmt::println(file, "int rows = {}, cols = {};", m_config.rows, m_config.cols);
    fmt::println(file, "Light onLight = {};", m_config.onLight);
    fmt::println(file, "Light offLight = {};", m_config.offLight);
    fmt::println(file, "wp.AmpRt = {};", m_config.AmpRt);
    fmt::println(file, "wp.wvLenLt = {};", m_config.wvLenLt);
    fmt::println(file, "wp.wvLenRt = {};", m_config.wvLenRt);
    fmt::println(file, "wp.wvSpdLt = {};", m_config.wvSpdLt);
    fmt::println(file, "wp.wvSpdRt = {};", m_config.wvSpdRt);
    fmt::println(file, "wp.C_Rt = C_Rt;");
    fmt::println(file, "wp.init(arr[0], rows, cols, onLight, offLight);");
    fmt::println(file, "}}");
}


void WavePlayerWrapper::Render(sf::RenderTarget &target) {
    BaseLightPlayerWrapper::Render(target);
}
