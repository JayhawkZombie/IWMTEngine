//
// Created by Kurt Slagle on 12/31/24.
//

#include "TimerManager.h"

static std::uint32_t CurrentTimerHandle = 0;

void TimerManager::Init()
{
    m_elapsedTime = 0.0;
}

void TimerManager::Tick(double delta) {
    m_elapsedTime += delta;
    // Ignoring delta I guess lol
    while (!m_timers.empty())
    {
        const Timer &timer = m_timers.top();
        if (m_elapsedTime >= timer.expiration)
        {
            timer.callback();

            if (timer.repeating)
            {
                Timer newTimer = timer;
                m_deferredAdditions.push_back(newTimer);
            }

            m_timers.pop();
        }
        else
        {
            break;
        }
    }

    // Process any late additions
    for (auto &timer : m_deferredAdditions)
    {
        timer.expiration = m_elapsedTime + timer.duration;
        m_timers.push(timer);
    }

    m_deferredAdditions.clear();
}

void TimerManager::AddTimer(double duration, bool repeat, const std::function<void()> cb) {
    Timer timer;
    timer.expiration = m_elapsedTime + duration;
    timer.duration = duration;
    // GlobalConsole->AddLog(EngineConsole::LogLevel::Debug, "[%lf] Adding timer with duration %lf expiring at %lf", m_elapsedTime, duration, timer.expiration);
    timer.repeating = repeat;
    timer.callback = cb;
    TimerHandle handle;
    handle.id = CurrentTimerHandle++;
    timer.handle = handle;
    m_deferredAdditions.push_back(timer);
}

void TimerManager::Render(sf::RenderWindow &window) {
    GameObject::Render(window);
}
