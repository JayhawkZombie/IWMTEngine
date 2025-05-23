//
// Created by Kurt Slagle on 5/15/25.
//

#pragma once

#include "WavePlayerWrapper.h"

class TrackNode {
public:
    TrackNode(double stamp, const std::string &newFileName = "");

    double seconds_stamp = 0.0;
    std::string newWaveConfigFilename{""};
};

class Track {
public:
    WavePlayerConfig m_backgroundConfig;
    WavePlayer m_background;

    bool m_isPlaying               = false;
    bool m_hasReachedEnd           = false;
    double m_current_seconds_stamp = 0.0;
    size_t m_current_node_index    = 0;
    std::vector<TrackNode> m_nodes;
    Light *m_lights;

    void Init(Light *lightArr, WavePlayerConfig bg, size_t idx = 0);
    WavePlayerConfig LoadNextNode(const std::string &newWaveConfigFilename);

    void Play();

    void SetBackground(const WavePlayerConfig &config);

    void Update(double delta);

    void StartNextNode(double overStep);
};

class Choreography {
public:
    void Init(Light *arr);

    void Update(double delta);

    void Start();

    Track m_track;
};

inline void Choreography::Start() {
    m_track.Play();
}
