//
// Created by Kurt Slagle on 12/30/24.
//

#include <Globals.h>
#include <Console/EngineConsole.h>
#include <Misc/IniConfig.h>
#include <Editor/Editor.h>
#include <Timing/TimerManager.h>
std::unique_ptr<TimerManager> GlobalTimerManager;
std::unique_ptr<EngineConsole> GlobalConsole;
std::unique_ptr<IniConfig> GlobalIniConfig;
std::unique_ptr<Editor> GlobalEditor;
std::vector<std::filesystem::path> Assets;
// std::unique_ptr<sf::RenderWindow> GlobalRenderWindow;

