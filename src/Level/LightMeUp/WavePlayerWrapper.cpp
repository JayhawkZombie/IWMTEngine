//
// Created by Kurt Slagle on 4/21/25.
//

#include "WavePlayerWrapper.h"
#include <Logging/LogFormatting.h>
#include <Editor/ImGuiHelpers.h>
#include <fstream>
#include <Globals.h>
#include <cereal/cereal.hpp>
#include <Serialization/SerializeTypes.h>
#include <cereal/archives/json.hpp>
#include <GeneratedSerializationData.h>

void WavePlayerWrapper::SetConfig(const WavePlayerConfig &config) {
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
    m_wavePlayer.setWaveData(m_config.AmpRt,
                             m_config.wvLenLt,
                             m_config.wvSpdLt,
                             m_config.wvLenRt,
                             m_config.wvSpdRt);
    m_wavePlayer.update(0.f);
    m_visual.update();
    GlobalConsole->Debug("C_RT %.3f %.3f %.3f", m_config.C_Rt[0], m_config.C_Rt[1], m_config.C_Rt[2]);
    m_wavePlayer.setSeriesCoeffs_Unsafe(m_config.C_Rt, 3, nullptr, 0);
    SetHasInit(true);
}

bool WavePlayerWrapper::RenderEditor() {
    bool edited                    = false;
    bool didSetSeries              = false;
    static char fileNameBuff[256]  = {'\0'};
    static char inputFileBuff[256] = {'\0'};

    if (EditorInputTextWithButton("Output file",
                                  fileNameBuff,
                                  256,
                                  "Output file")) {
        SaveConfig(std::string(fileNameBuff));
    }

    if (EditorInputTextWithButton("Input file",
                                  inputFileBuff,
                                  256,
                                  "Input file")) {
        LoadConfig(std::string(inputFileBuff));
        Init();
    }
    if (ImGui::Button("Generate Code")) {
        GlobalConsole->Debug("Generating code for WavePlayer");
        GenerateCode();
    }
    edited = EditorLight(m_config.offLight, "Lo light");
    ImGui::SameLine();
    edited = edited || EditorLight(m_config.onLight, "Hi light");
    if (ImGui::SliderFloat3("C_Rt", &m_config.C_Rt[0], 0.f, 20.f, "%.3f")) {
        didSetSeries = true;
    }
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
    fmt::println(file,
                 "static float C_Rt[3] = {{{},{},{}}};",
                 m_config.C_Rt[0],
                 m_config.C_Rt[1],
                 m_config.C_Rt[2]);
    fmt::println(file,
                 "int rows = {}, cols = {};",
                 m_config.rows,
                 m_config.cols);
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

bool WavePlayerWrapper::LoadConfig(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        GlobalConsole->Error("Could not open file for wave data %s",
                             filename.c_str());
        return false;
    }

    cereal::JSONInputArchive archive(file);
    archive(cereal::make_nvp("waveData", m_config));
    GlobalConsole->Info("Loaded WaveData from file %s", filename.c_str());
    return true;
}


bool WavePlayerWrapper::SaveConfig(const std::string &filename) {
    std::ofstream file(filename);
    if (!file) {
        GlobalConsole->Error("Could not open file for saving wave data %s",
                             filename.c_str());
        return false;
    }

    GlobalConsole->Debug("Saving wave data to %s", filename.c_str());
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("waveData", m_config));
    return true;
}


void WavePlayerWrapper::Render(sf::RenderTarget &target) {
    BaseLightPlayerWrapper::Render(target);
}
