//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once
#include <chrono>

class RealTimeClock {
public:

    using clock_t = typename std::chrono::high_resolution_clock;
    using time_point_t = typename clock_t::time_point;
    using duration_t = typename std::chrono::microseconds;

    using millisecond_duration_t = typename std::chrono::duration<double, std::milli>;
    using seconds_duration_t = typename std::chrono::duration<double, std::ratio<1LL,1LL>>;

    static millisecond_duration_t ToMilliseconds(const duration_t &dur) {
        return std::chrono::duration_cast<millisecond_duration_t>(dur);
    }

    static seconds_duration_t ToSeconds(const duration_t &dur) {
        return std::chrono::duration_cast<seconds_duration_t>(dur);
    }

    RealTimeClock() {
        Restart();
    }

    void Restart() {
        m_isPaused = false;
        m_startTime = GetRealNow();
    }

    void Pause() {
        m_isPaused = true;
        m_pauseTime = GetRealNow();
    }

    void Resume() {
        m_isPaused = false;
        const time_point_t now = GetRealNow();
        // Scoot starting time up time we were paused by
        const auto elapsed_time_paused = std::chrono::duration_cast<duration_t>(now - m_pauseTime);
        m_startTime += elapsed_time_paused;
    }

    duration_t GetTimeSinceStart() {
        return std::chrono::duration_cast<duration_t>(
            GetNow() - m_startTime
        );
    }

    static duration_t GetDelta(time_point_t t1, time_point_t t2) {
        return std::chrono::duration_cast<duration_t>(
            t1 - t2
        );
    }

    time_point_t GetNow() {
        // Return actual now - paused time (if paused)
        const time_point_t actualNow = GetRealNow();
        if (m_isPaused) {
            return time_point_t(actualNow - m_pauseTime);
        }
        return actualNow;
    }

private:

    time_point_t GetRealNow() {
        return clock_t::now();
    }

    time_point_t m_startTime;
    time_point_t m_pauseTime;
    bool m_isPaused = false;

};
