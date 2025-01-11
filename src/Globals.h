//
// Created by Kurt Slagle on 12/30/24.
//

#pragma once

#include <memory>

#include <Console/EngineConsole.h>

class TimerManager;
class IniConfig;

extern std::unique_ptr<TimerManager> GlobalTimerManager;
extern std::unique_ptr<EngineConsole> GlobalConsole;
extern std::unique_ptr<IniConfig> GlobalIniConfig;
