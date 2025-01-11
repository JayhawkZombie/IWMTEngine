//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <cstdint>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct TimerHandle
{
    std::uint32_t id = 0;

    bool operator == (const TimerHandle &Handle) const
    {
        return id == Handle.id;
    }

    bool operator != (const TimerHandle &Handle) const
    {
        return id != Handle.id;
    }
};

struct Timer
{
    double expiration = 0.0;
    double duration {0};
    bool paused = false;
    bool repeating = false;
    std::function<void()> callback = [](){};
    TimerHandle handle{};

    Timer() = default;
    Timer (const Timer &other)
    {
        expiration = other.expiration;
        duration = other.duration;
        paused = other.paused;
        repeating = other.repeating;
        callback = other.callback;
        handle = other.handle;
    }

    inline friend bool operator < (const Timer &t1, const Timer &t2)
    {
        return t1.expiration > t2.expiration;
    }

    bool operator == (const Timer &t) const
    {
        return handle == t.handle;
    }

    bool operator != (const Timer &t) const
    {
        return handle != t.handle;
    }
};
