//
// Created by Kurt Slagle on 4/5/25.
//

#include "Editor.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <Logging/LogFormatting.h>
#include <Misc/IconsFontAwesome6.h>
#include <GeneratedSerializationData.h>
#include <Level/Level.h>

Editor::Editor(Engine *instance) : m_engineInstance(instance) {
}

void Editor::Render() {
    DisplayLevelDropdown();
}


void Editor::DisplayLevelDropdown() {
    static int currentItem    = 0;
    char const *currLevelName = nullptr;
    if (!Engine::PossibleLevelFiles.empty()) {
        currLevelName = Engine::PossibleLevelFiles[currentItem].
                c_str();
    }
    ImGui::Text("Selected Level: %s", currLevelName ? currLevelName : "<None>");
    // if (ImGui::Begin("Level Selector")) {
    if (!Engine::PossibleLevelFiles.empty()) {
        // Create the combo box directly from the vector of strings
        if (ImGui::Combo("Select Level",
                         &currentItem,
                         [](void *data, int idx, const char **out_text) {
                             auto &items = *static_cast<std::vector<std::string>
                                 *>(data);
                             if (idx >= 0 && idx < items.size()) {
                                 *out_text = items[idx].c_str();
                                 return true;
                             }
                             return false;
                         },
                         &(Engine::PossibleLevelFiles),
                         Engine::PossibleLevelFiles.size())) {
            // When a new item is selected, update the level
            if (currentItem >= 0 && currentItem < Engine::PossibleLevelFiles.size()) {
                const auto& selectedLevel = Engine::PossibleLevelFiles
                        [currentItem];
                // Extract the level name from the file path
                std::filesystem::path path(selectedLevel);
                std::string levelName = path.stem().string();

                // Update the config and reload the level
                m_engineInstance->config.game.levelName = levelName;
                m_engineInstance->SaveConfig("config.json");
                m_engineInstance->InitLevel();
            }
        }
    } else {
        ImGui::Text("No level files found");
    }
    if (ImGui::Button(ICON_FA_FILE)) {
        std::ofstream configFile("level0.level");
        if (!configFile) {
            fmt::println("Failed to open config file for writing {}",
                         fmt::styled("level0.level", fg_color_green));
            return;
        }

        cereal::JSONOutputArchive outArchive(configFile);
        if (m_engineInstance->maybeLevelPtr) {

            try {
                if (auto lvl = m_engineInstance->maybeLevelPtr->try_cast<Level>()) {
                    outArchive(*lvl);
                } else {
                    GlobalConsole->Error("Failed to save level");
                }
            } catch (const std::runtime_error &error) {
                GlobalConsole->Error("Exception while saving level: %s", error.what());
            }

        }
    }
}
