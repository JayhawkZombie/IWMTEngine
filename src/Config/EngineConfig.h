//
// Created by Kurt Slagle on 1/2/25.
//

#pragma once
#include <string>
#include <Physics/Physics.h>
#include <Reflection/GenReflection.h>

struct PhysicsConfig {
    vec2d gravity = {0.0, -9.81};
};

RENGINE_REFLECT_CLASS_BEGIN(PhysicsConfig)
    RENGINE_REFLECT_CLASS_MEMBER(vec2d, gravity, "gravity")
RENGINE_REFLECT_CLASS_END(PhysicsConfig)

struct WindowConfig {
    int width               = 800;
    int height              = 600;
    bool enableVSync        = true;
    bool enableMsaa         = true;
    bool enableFullscreen   = false;
    bool enableResize       = true;
    int frameRate           = 60;
    std::string windowTitle = "REngine";
};

RENGINE_REFLECT_CLASS_BEGIN(WindowConfig)
    RENGINE_REFLECT_CLASS_MEMBER(int, width, "width")
    RENGINE_REFLECT_CLASS_MEMBER(int, height, "height")
    RENGINE_REFLECT_CLASS_MEMBER(bool, enableVSync, "enableVSync")
    RENGINE_REFLECT_CLASS_MEMBER(bool, enableMsaa, "enableMsaa")
    RENGINE_REFLECT_CLASS_MEMBER(bool, enableFullscreen, "enableFullscreen")
    RENGINE_REFLECT_CLASS_MEMBER(bool, enableResize, "enableResize")
    RENGINE_REFLECT_CLASS_MEMBER(int, frameRate, "frameRate")
    RENGINE_REFLECT_CLASS_MEMBER(bool, windowTitle, "windowTitle")
RENGINE_REFLECT_CLASS_END(WindowConfig)

struct CoreConfig {
    std::string defaultFont;
    bool startEditorPaused = true;
};

RENGINE_REFLECT_CLASS_BEGIN(CoreConfig)
    RENGINE_REFLECT_CLASS_MEMBER(std::string, defaultFont, "defaultFont")
    RENGINE_REFLECT_CLASS_MEMBER(bool, startEditorPaused, "startEditorPaused")
RENGINE_REFLECT_CLASS_END(CoreConfig)

struct GameInitConfig {
    std::string levelName;
};

RENGINE_REFLECT_CLASS_BEGIN(GameInitConfig)
    RENGINE_REFLECT_CLASS_MEMBER(std::string, levelName, "levelName")
RENGINE_REFLECT_CLASS_END(GameInitConfig)

struct EngineConfig {
    CoreConfig core;
    WindowConfig window;
    PhysicsConfig physics;
    GameInitConfig game;
};

RENGINE_REFLECT_CLASS_BEGIN(EngineConfig)
    RENGINE_REFLECT_CLASS_MEMBER(EngineConfig, core, "core")
    RENGINE_REFLECT_CLASS_MEMBER(EngineConfig, window, "window")
    RENGINE_REFLECT_CLASS_MEMBER(EngineConfig, physics, "physics")
    RENGINE_REFLECT_CLASS_MEMBER(EngineConfig, game, "game")
RENGINE_REFLECT_CLASS_END(EngineConfig)
