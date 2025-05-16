//
// Created by Kurt Slagle on 5/14/25.
//

#pragma once

#include <chrono>
#include <Globals.h>
#include <Console/EngineConsole.h>
#include <string>

class Benchmark {
public:

    using benchmark_time_point_t = std::chrono::high_resolution_clock::time_point;
    using benchmark_duration_t = std::chrono::high_resolution_clock::duration;

    Benchmark(const std::string &name, bool autoStart = false) : m_name(name) {
        if (autoStart) {
            Start();
        }
    }
    virtual ~Benchmark() {
        if (m_running) {
            GlobalConsole->Debug("Benchmark destroyed before being stopped %s", m_name.c_str());
        }
    }

    void Start() {
        m_start_time = std::chrono::high_resolution_clock::now();
        m_running = true;
        m_finished = false;
    }

    void Stop() {
        m_running = false;
        m_finished = true;
        m_end_time = std::chrono::high_resolution_clock::now();
    }

    benchmark_duration_t GetDuration() const {
        return std::chrono::duration_cast<benchmark_duration_t>(m_end_time - m_start_time);
    }

    bool IsRunning() const {
        return m_running;
    }

    bool IsFinished() const {
        return m_finished;
    }

    const std::string& GetName() const {
        return m_name;
    }

private:

    bool m_running = false;
    bool m_finished = false;

    benchmark_time_point_t m_start_time;
    benchmark_time_point_t m_end_time;

    std::string m_name;

};
