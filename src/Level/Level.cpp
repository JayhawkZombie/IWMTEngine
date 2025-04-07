//
// Created by Kurt Slagle on 1/4/25.
//

#include "Level.h"

#include <imgui.h>
#include <Logging/LogFormatting.h>

Level::Level() {
    fmt::println("{}",
                 fmt::styled("Level::Level()",
                             fg_color_magenta | fmt::emphasis::italic));
}

Level::~Level() {
    fmt::println("{}",
        fmt::styled("Level::~Level()", fg_color_magenta | fmt::emphasis::italic));
}

void Level::Init() {
    isInitialized = true;
    fmt::println("{} - override to customize initialization",
        fmt::styled("Level::Init()", fg_color_magenta | fmt::emphasis::italic));
}

void Level::Destroy() {
    fmt::println("{} - override to customize destruction",
        fmt::styled("Level::Destroy()", fg_color_magenta | fmt::emphasis::italic));
}

void Level::Render(sf::RenderTarget &target) {
}

bool Level::RenderLevelEditor() {
    bool edited = false;
    if (ImGui::Begin("Level Editor")) {
        edited = this->RenderEditor();
    }
    ImGui::End();
    return edited;
}


void Level::Tick(double delta) {
}

bool Level::RenderEditor() {
    return false;
}

bool Level::IsInitialized() {
    return isInitialized;
}

void Level::SetIsInitialized(bool isInit) {
    isInitialized = isInit;
}
