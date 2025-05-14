//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

#include <memory>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <Console/EngineConsole.h>

class TimerManager;
class IniConfig;
class Editor;

extern std::unique_ptr<TimerManager> GlobalTimerManager;
extern std::unique_ptr<EngineConsole> GlobalConsole;
extern std::unique_ptr<IniConfig> GlobalIniConfig;
extern std::unique_ptr<Editor> GlobalEditor;
extern std::vector<std::filesystem::path> Assets;

// extern std::unique_ptr<sf::RenderWindow> GlobalRenderWindow;
