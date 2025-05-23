//
// Created by Kurt Slagle on 5/15/25.
//

#include "Choreography.h"
#include <GeneratedSerializationData.h>
#include <Console/EngineConsole.h>
#include <Assets/AssetLoader.h>

TrackNode::TrackNode(double stamp, const std::string &newFilename): seconds_stamp{stamp}, newWaveConfigFilename{newFilename} {
}

void Track::Init(Light *lightArr, WavePlayerConfig bg, size_t idx) {
    GlobalConsole->Debug("Init track");
    m_backgroundConfig = bg;
    m_lights           = lightArr;
    m_current_node_index = idx;
    m_current_seconds_stamp = 0.0;
    m_background.init(*m_lights,
                      m_backgroundConfig.rows,
                      m_backgroundConfig.cols,
                      m_backgroundConfig.onLight,
                      m_backgroundConfig.offLight);
    m_background.setWaveData(m_backgroundConfig.AmpRt,
                         m_backgroundConfig.wvLenLt,
                         m_backgroundConfig.wvSpdLt,
                         m_backgroundConfig.wvLenRt,
                         m_backgroundConfig.wvSpdRt);
    if (m_backgroundConfig.useRightCoefficients || m_backgroundConfig.useLeftCoefficients) {
        m_background.setSeriesCoeffs_Unsafe(
                                            m_backgroundConfig.useRightCoefficients
                                                ? m_backgroundConfig.C_Rt
                                                : nullptr,
                                            m_backgroundConfig.useRightCoefficients
                                                ? 3
                                                : 0,
                                            m_backgroundConfig.useLeftCoefficients
                                                ? m_backgroundConfig.C_Lt
                                                : nullptr,
                                            m_backgroundConfig.useLeftCoefficients ? 3 : 0
                                           );
    }
    m_background.setRightTrigFunc(m_backgroundConfig.rightTrigFuncIndex);
    m_background.setLeftTrigFunc(m_backgroundConfig.leftTrigFuncIndex);
    m_background.update(0.f);
}

WavePlayerConfig Track::LoadNextNode(const std::string &newWaveConfigFilename) {
    WavePlayerConfig config;
    LoadJSONAsset(newWaveConfigFilename, "waveData", config);
    return config;
}

void Track::Play() {
    m_isPlaying             = true;
    m_current_seconds_stamp = 0;
    m_current_node_index    = 0;
}

void Track::SetBackground(const WavePlayerConfig &config) {
    GlobalConsole->Debug("Setting background config");
    Init(m_lights, config);
}

void Track::Update(double delta) {
    if (m_nodes.empty() || !m_isPlaying) {
        return;
    }

    m_background.update(static_cast<float>(delta));

    m_current_seconds_stamp += delta;
    const auto &node = m_nodes[m_current_node_index];
    if (m_current_seconds_stamp >= node.seconds_stamp) {
        GlobalConsole->Debug("Trying to go to next node (from %s)", node.newWaveConfigFilename.c_str());
        StartNextNode(m_current_seconds_stamp - node.seconds_stamp);
    } else {
        // ? Update current running patterns, however we do that
    }
}

void Track::StartNextNode(double overStep) {
    if (m_current_node_index == m_nodes.size() - 1) {
        // Can't advance
        GlobalConsole->Debug("Cannot advance track, at end");
        m_hasReachedEnd = true;
        m_isPlaying = false;
        return;
    }

    m_current_node_index += 1;
    GlobalConsole->Error("Starting next node %lu out of %llu", m_current_node_index, m_nodes.size());
    m_current_seconds_stamp = overStep;
    const auto node = m_nodes[m_current_node_index];
    // Init & update next player with overStep
    GlobalConsole->Error("Next config name %s", node.newWaveConfigFilename.c_str());
    const auto config = LoadNextNode(node.newWaveConfigFilename);
    Init(m_lights, config, m_current_node_index);
}

void Choreography::Init(Light *arr) {
    WavePlayerConfig config;
    GlobalConsole->Info("Choreography::Init");
    LoadJSONAsset("wave-files/rain_better.wave", "waveData", config);
    m_track.Init(arr, config);
    m_track.m_nodes.push_back({1.0, "wave-files/rain_better.wave"});
    m_track.m_nodes.push_back({2.0, "wave-files/rain.wave"});
}

void Choreography::Update(double delta) {
    m_track.Update(delta);
}
