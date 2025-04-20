//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <Engine/GameObject.h>
#include <queue>
#include <Timing/Timer.h>

class TimerManager : public GameObject
{
public:
    TimerManager() = default;

    void Tick(double delta) override;
    void Init() override;

    void AddTimer(
        double duration,
        bool repeat,
        const std::function<void()> cb
    );

    void Render(sf::RenderTarget &target) override;

private:

    double m_elapsedTime = 0.0;

    std::priority_queue<Timer> m_timers;
    std::vector<Timer> m_deferredAdditions;
    std::vector<Timer> m_stoppedTimers;
};
