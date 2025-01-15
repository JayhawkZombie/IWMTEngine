#include <Engine/Engine.h>
#include <GeneratedSerializationData.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include <spdlog/spdlog.h>

int main() {
    spdlog::set_pattern("[%n:%t] - %v");
    spdlog::info("Test!");
    Engine engine;
    engine.Init();
    return engine.Run();
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
