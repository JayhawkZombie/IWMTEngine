//
// Created by Kurt Slagle on 4/21/25.
//

#pragma once

#include "BaseLightPlayerWrapper.h"
#include "Light_types/WavePlayer.h"

struct WavePlayerConfig {
    int rows, cols;
    Light onLight, offLight;
    bool useRightCoefficients = true;
    bool useLeftCoefficients = false;
    float C_Rt[3] = {3, 2, 1};
    float C_Lt[3] = {0, 0, 0};
    float AmpLt, AmpRt;
    float wvLenLt, wvLenRt;
    float wvSpdLt, wvSpdRt;
};

class WavePlayerWrapper : public BaseLightPlayerWrapper {
public:
    void SetConfig(const WavePlayerConfig &config);

    WavePlayerConfig m_config;

    ~WavePlayerWrapper() override;

    virtual void Tick(double delta) override;
    virtual void Init() override;
    virtual void Render(sf::RenderTarget &target) override;
    virtual bool RenderEditor() override;
    bool RenderEditorRuntimeValues();
    bool RenderGallery();
    void GenerateCode() override;
    bool SaveConfig(const std::string &filename) override;
    bool LoadConfig(const std::string &filename) override;
    void SetBoxes(const sf::Vector2f &boxSize, const sf::Vector2f &boxSpacing);

    void TryToIndexWaveFiles();
    double accumTime = 0.0;
    float updateScale = 1.f;
    bool m_showGallery = false;

    sf::Vector2f m_boxSize    = sf::Vector2f(8.f, 8.f);
    sf::Vector2f m_boxSpacing = sf::Vector2f(4.f, 4.f);
    std::vector<std::string> m_preConfiguredWaves;
    WavePlayer m_wavePlayer;
};

#include <Reflection/GenReflection.h>

RENGINE_REFLECT_CLASS_BEGIN(WavePlayerConfig)
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, rows, "rows")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, cols, "cols")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, onLight, "onLight")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, offLight, "offLight")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, C_Rt, "C_Rt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, C_Lt, "C_Lt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, useRightCoefficients, "useRightCoefficients")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, useLeftCoefficients, "useLeftCoefficients")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, AmpLt, "AmpLt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, AmpRt, "AmpRt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, wvLenLt, "wvLenLt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, wvLenRt, "wvLenRt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, wvSpdLt, "wvSpdLt")
RENGINE_REFLECT_CLASS_MEMBER(WavePlayerConfig, wvSpdRt, "wvSpdRt")
RENGINE_REFLECT_CLASS_END(WavePlayerConfig)
