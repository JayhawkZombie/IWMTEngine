//
// Created by Kurt Slagle on 4/25/25.
//

#pragma once

#include "BaseLightPlayerWrapper.h"
#include "Light_types/PulsePlayer.h"

class PulsePlayerWrapper : public BaseLightPlayerWrapper {
public:
    struct config {
        int rows, cols;
        Light defaultColor;
        Light hiLight, lowLight;
        float W_pulse, speed, T_repeat;
        bool repeat = false;
        sf::Vector2f boxSpacing;
        sf::Vector2f boxSize;
    } m_config;

    ~PulsePlayerWrapper() override;

    void SetConfig(const config &config);

    virtual void Tick(double delta) override;
    virtual void Init() override;
    virtual void Render(sf::RenderTarget &target) override;
    virtual bool RenderEditor() override;
    void GenerateCode() override;

private:
    PulsePlayer m_pulsePlayer;
};
