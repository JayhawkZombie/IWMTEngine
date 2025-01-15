//
// Created by Kurt Slagle on 1/4/25.
//

#include <fstream>
#include <Logging/LogFormatting.h>
#include "SpriteSheet.h"
#include <imgui.h>
#include <Misc/IconsFontAwesome6.h>
#include <Editor/ImGuiHelpers.h>

SpriteSheet::SpriteSheet(const std::string &fileName) {
    if (!Load(fileName)) {
        fmt::println("Failed to load sprite sheet file {}", fileName);
    }
}

bool SpriteSheet::Load(const std::string &fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        fmt::print("Failed to open sprite sheet file {}", fileName);
        return false;
    }

    const auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(fileName)) {
        fmt::print("Failed to load sprite sheet texture {}", fileName);
        return false;
    }
    originalFileName = fileName;
    texture          = tex;
    return true;
}

void SpriteSheet::Render(sf::RenderTarget &target,
                         const sf::Vector2f &position) {
    sf::Sprite sprite;
    sprite.setTexture(*texture, true);
    sprite.setPosition(position);
    target.draw(sprite);
}

void SpriteSheet::RenderEditor() {
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_None | ImGuiWindowFlags_MenuBar;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR",
                      ImVec2(0, 260),
                      ImGuiChildFlags_Borders,
                      window_flags);
    if (ImGui::BeginMenuBar()) {
        RenderMenuBar();
        ImGui::EndMenuBar();
    }
    RenderDimensionsEditor();
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

void SpriteSheet::RenderMenuBar() {
    if (ImGui::MenuItem("New Frame")) {
        RenderFrameEditorPopup();
    }
}

void SpriteSheet::RenderFrameEditorPopup() {
    static int selected_frame_index = 0;
    if (ImGui::BeginPopup("SpriteSheet:Frames", ImGuiWindowFlags_MenuBar)) {
        if (rawFrames.empty()) {
            ImGui::Text("There are no sprite frames");
        } else if (rawFrames.size() == 1) {
            RenderFrameEditorForFrame(0);
        } else {
            if (ImGui::Button(ICON_FA_CARET_LEFT)) {
                selected_frame_index = std::max(selected_frame_index - 1, 0);
            }
            ImGui::SameLine();
            for (int i = 0; i < rawFrames.size(); i++) {
                if (ImGui::SmallButton(std::to_string(i).c_str())) {
                    selected_frame_index = i;
                }
                ImGui::SameLine();
            }
            if (ImGui::Button(ICON_FA_CARET_RIGHT)) {
                selected_frame_index = std::min(selected_frame_index + 1,
                                                static_cast<int>(rawFrames.
                                                    size()) - 1);
            }
        }
        ImGui::Separator();
        ImGui::EndPopup();
    }
}

void SpriteSheet::RenderFrameEditorForFrame(int frame) {
}

void SpriteSheet::RenderDimensionsEditor() {
    ImGui::SeparatorText("Dimensions and Size");
    if (texture) {
        ImGui::Text("Texture");
        ImGui::SameLine();
        ImGui::TextColored(ImGuiColors::BrightPink, "%i", texture->getSize().x);
        ImGui::SameLine();
        ImGui::Text("x");
        ImGui::SameLine();
        ImGui::TextColored(ImGuiColors::BrightPink, "%i", texture->getSize().y);
    }
}
