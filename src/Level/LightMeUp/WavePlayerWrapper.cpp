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
    m_wavePlayer.update(updateScale * static_cast<float>(delta));
    accumTime += delta;
    if (accumTime >= 2.0) {
        accumTime = 0.0;
        TryToIndexWaveFiles();
    }
}

void WavePlayerWrapper::Init() {
    static float C_Lt[3] = {0, 0, 0};
    BaseLightPlayerWrapper::Init();
    GlobalConsole->Debug("Init wave player, %i X %i",
                         m_config.rows,
                         m_config.cols);
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
    if (m_config.useRightCoefficients || m_config.useLeftCoefficients) {
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
                                            m_config.useLeftCoefficients ? 3 : 0
                                           );
        GlobalConsole->Debug("C_Rt %.3f %.3f %.3f",
                             m_config.C_Rt[0],
                             m_config.C_Rt[1],
                             m_config.C_Rt[2]);
        GlobalConsole->Debug("C_Lt %.3f %.3f %.3f",
                             m_config.C_Lt[0],
                             m_config.C_Lt[1],
                             m_config.C_Lt[2]);
    }
    SetHasInit(true);
    TryToIndexWaveFiles();
}

void WavePlayerWrapper::Render(sf::RenderTarget &target) {
    BaseLightPlayerWrapper::Render(target);
}
