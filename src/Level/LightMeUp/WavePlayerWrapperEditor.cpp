//
// Created by Kurt Slagle on 5/4/25.
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
#include <Assets/AssetLoader.h>
#include <Editor/ImGuiClasses.h>

bool WavePlayerWrapper::RenderEditor() {
    bool edited                        = false;
    static char fileNameBuff[256]      = {'\0'};
    static unsigned int preConfigIndex = 0;

    if (m_preConfiguredWaves.size() < preConfigIndex) {
        preConfigIndex = 0;
    } {
        ImGuiHelpers::Group _group("General", "general", true);
        ImGui::SetNextItemWidth(50.f);
        if (ImGui::SliderFloat("Update scale", &updateScale, 0.01f, 5.f)) {
            edited = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Gallery")) {
            edited = true;
            ImGui::OpenPopup("WavePlayerGallery");
            m_showGallery = true;
        }

        ImGui::SetNextItemWidth(150.f);
        if (ImGui::SliderInt("Width", &m_config.cols, 0, 256)) {
            edited = true;
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150.f);
        if (ImGui::SliderInt("Height", &m_config.rows, 0, 256)) {
            edited = true;
        }

        if (EditorInputTextWithButton("##WaveOutput",
                                      fileNameBuff,
                                      256,
                                      "Save")) {
            std::string filename = std::string(fileNameBuff);
            std::filesystem::path path(filename);
            if (path.extension() == ".wave") {
                SaveConfig(std::string(fileNameBuff));
            } else {
                GlobalConsole->Error("Cannot save file, invalid");
            }
        }
    }
    static bool listItemChanged = false;
    listItemChanged             = false; {
        ImGuiHelpers::Group _group("Input Files", "input-files", false);
        if (EditorComboListbox("Input files",
                               m_preConfiguredWaves,
                               preConfigIndex,
                               listItemChanged)) {
            // Nothing yet
            // selectedConfigItem = true;
            memset(fileNameBuff, 0, sizeof(fileNameBuff));
            memcpy(fileNameBuff,
                   m_preConfiguredWaves[preConfigIndex].c_str(),
                   sizeof(char) * std::min(static_cast<size_t>(256),
                                           m_preConfiguredWaves[preConfigIndex].
                                           size()));
            LoadConfig(m_preConfiguredWaves[preConfigIndex]);
            edited = true;
        }
    }

    ImGui::SeparatorText("Runtime Values");
    if (RenderEditorRuntimeValues()) {
        edited = true;
    }
    if (RenderGallery()) {
        // Nothing to do here, but this does not indicate an edit
    }

    if (edited) {
        Init();
        GlobalConsole->Debug("Edited, might set series coeff {} {}", m_config.useLeftCoefficients, m_config.useRightCoefficients);
        m_wavePlayer.setSeriesCoeffs_Unsafe(
                                            m_config.useRightCoefficients
                                                ? m_config.C_Rt
                                                : nullptr,
                                            m_config.useRightCoefficients
                                                ? 3
                                                : 0,
                                            m_config.useLeftCoefficients
                                                ? m_config.C_Lt
                                                : nullptr,
                                            m_config.useLeftCoefficients
                                                ? 3
                                                : 0);
    }

    return edited;
}

bool WavePlayerWrapper::RenderEditorRuntimeValues() {
    bool edited       = false;
    bool didSetSeries = false;
    static std::vector<std::string> trigFuncIndices{
        "sinf",
        "cosf",
        "tanf",
        "hypotf",
        "sinh",
        "cosh",
        "tanh",
        std::string("sawtooth")
    };
    static bool selectedTrigFunctionChanged    = false;
    selectedTrigFunctionChanged                = false;
    if (EditorLight(m_config.offLight, "Lo light")) {
        edited = true;
    }
    ImGui::SameLine();
    if (EditorLight(m_config.onLight, "Hi light")) {
        edited = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Generate Code")) {
        GlobalConsole->Debug("Generating code for WavePlayer");
        GenerateCode();
    } {
        ImGuiHelpers::Group _group("Series Coefficients", "series_coeff", true);
        if (ImGui::Checkbox("Right", &m_config.useRightCoefficients)) {
            didSetSeries = true;
            edited       = true;
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(400.f);
        if (ImGui::SliderFloat3("##C_Rt",
                                &m_config.C_Rt[0],
                                0.f,
                                20.f,
                                "%.3f")) {
            edited       = true;
            didSetSeries = true;
        }
        if (ImGui::Checkbox("Left", &m_config.useLeftCoefficients)) {
            didSetSeries = true;
            edited       = true;
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(400.f);
        if (ImGui::SliderFloat3("##C_Lt",
                                &m_config.C_Lt[0],
                                0.f,
                                20.f,
                                "%.3f")) {
            didSetSeries = true;
            edited       = true;
        }
    } { // Group all waveform stuff together
        ImGuiHelpers::Group _group("Waveforms", "waveform_values", true);

            {
                ImGuiHelpers::Group _leftFuncGroup("LeftTrigFunc",
                                                   "left_func_group",
                                                   false);
                if (EditorComboListbox("Left Trig function",
                                       trigFuncIndices,
                                       m_config.leftTrigFuncIndex,
                                       selectedTrigFunctionChanged,
                                       ImVec2(150.f, 75.f))) {
                    edited = true;
                    // m_wavePlayer.setLeftTrigFunc(selectedLeftFuncIndex);
                }
            }
        ImGui::SameLine();
            {
                ImGuiHelpers::Group _rightFuncGroup("RightTrigFunc", "right_func_group", false);
                if (EditorComboListbox("Right Trig function",
                                       trigFuncIndices,
                                       m_config.rightTrigFuncIndex,
                                       selectedTrigFunctionChanged,
                                       ImVec2(150.f, 75.f))) {
                    edited = true;
                    // m_wavePlayer.setRightTrigFunc(selectedRightFuncIndex);
                }
            }
            // ImGui::SameLine();

        ImGui::Text("Amplitude");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.f);
        if (ImGui::SliderFloat("##Amp Rt", &m_config.AmpRt, 0.f, 5.f, "%.3f")) {
            edited = true;
        }

        ImGui::BeginGroup();
        ImGui::Text("Wavelength");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.f);
        if (ImGui::SliderFloat("##WvLn Lt",
                               &m_config.wvLenLt,
                               0.f,
                               128.f,
                               "%.3f")) {
            edited = true;
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.f);
        if (ImGui::SliderFloat("##WvLn Rt",
                               &m_config.wvLenRt,
                               0.f,
                               128.f,
                               "%.6f")) {
            edited = true;
        }
        ImGui::EndGroup();
        // Wave speed values, grouped
        ImGui::BeginGroup();
        ImGui::Text("Wave Speed");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.f);
        if (ImGui::SliderFloat("##WvSpd Lt",
                               &m_config.wvSpdLt,
                               0.f,
                               128.f,
                               "%.6f")) {
            edited = true;
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200.f);
        if (ImGui::SliderFloat("##WvSpd Rt",
                               &m_config.wvSpdRt,
                               0.f,
                               128.f,
                               "%.3f")) {
            edited = true;
        }
        ImGui::EndGroup();
    }
    return edited || didSetSeries;
}


bool WavePlayerWrapper::RenderGallery() {
    bool interacted = false;
    ImVec2 center   = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("WavePlayerGallery",
                               nullptr,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        interacted = true;
        if (ImGui::Button("Gallery")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }


    return interacted;
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
    if (m_config.useRightCoefficients) {
        fmt::println(file,
                     "static float C_Rt[3] = {{{},{},{}}};",
                     m_config.C_Rt[0],
                     m_config.C_Rt[1],
                     m_config.C_Rt[2]);
    }
    if (m_config.useLeftCoefficients) {
        fmt::println(file,
                     "static float C_Lt[3] = {{{},{},{}}};",
                     m_config.C_Lt[0],
                     m_config.C_Lt[1],
                     m_config.C_Lt[2]);
    }
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
    fmt::println(file,
                 "wp.setRightTrigFunc({});",
                 m_config.rightTrigFuncIndex);
    fmt::println(file,
                 "wp.setLeftTrigFunc({});",
                 m_config.leftTrigFuncIndex);
    if (m_config.useRightCoefficients) {
        fmt::println(file, "wp.C_Rt = C_Rt;");
    }
    if (m_config.useLeftCoefficients) {
        fmt::println(file, "wp.C_Lt = C_Lt;");
    }
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

    // LoadJSONAsset(filename, "waveData", m_config);
    if (!LoadConfigFile(filename, m_config)) {
        GlobalConsole->Error("Could not load wave data %s", filename.c_str());
        return false;
    }
    // cereal::JSONInputArchive archive(file);
    // archive(cereal::make_nvp("waveData", m_config));
    GlobalConsole->Info("Loaded WaveData from file %s", filename.c_str());
    return true;
}

bool WavePlayerWrapper::LoadConfigFile(const std::string &filename,
    WavePlayerConfig &config) {
    try {
        LoadJSONAsset(filename, "waveData", config);
    } catch (const std::exception &e) {
        GlobalConsole->Error("Exception while loading wave data from %s: %s", filename.c_str(), e.what());
        return false;
    }

    return true;
}

void WavePlayerWrapper::SetBoxes(const sf::Vector2f &boxSize,
                                 const sf::Vector2f &boxSpacing) {
    m_boxSize    = boxSize;
    m_boxSpacing = boxSpacing;
    Init();
}

void WavePlayerWrapper::TryToIndexWaveFiles() {
    // Index pre-configured wave patterns
    m_preConfiguredWaves.clear();
    for (const auto &asset: Assets) {
        if (asset.has_extension() && asset.extension() == ".wave") {
            const auto relPath = std::filesystem::relative(asset, "./");
            WavePlayerConfig config;
            if (LoadConfigFile(relPath.string(), config)) {
                m_preloadedConfigs[relPath.string()] = config;
                m_preConfiguredWaves.push_back(relPath.string());
            } else {
                // Hmmm....
            }
        }
    }
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
