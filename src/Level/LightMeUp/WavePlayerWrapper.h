//
// Created by Kurt Slagle on 4/21/25.
//

#pragma once

#include "BaseLightPlayerWrapper.h"
#include "Light_types/WavePlayer.h"

class WavePlayerWrapper : public BaseLightPlayerWrapper {
public:
    struct config {
        int rows, cols;
        Light onLight, offLight;
        float C_Rt[3] = {3, 2, 1};
        float AmpLt, AmpRt;
        float wvLenLt, wvLenRt;
        float wvSpdLt, wvSpdRt;
    };


    void SetConfig(const config &config);

    config m_config;

    ~WavePlayerWrapper() override;

    virtual void Tick(double delta) override;
    virtual void Init() override;
    virtual void Render(sf::RenderTarget &target) override;
    virtual bool RenderEditor() override;
    void GenerateCode() override;

    sf::Vector2f m_boxSize    = sf::Vector2f(8.f, 8.f);
    sf::Vector2f m_boxSpacing = sf::Vector2f(4.f, 4.f);
    WavePlayer m_wavePlayer;
};
