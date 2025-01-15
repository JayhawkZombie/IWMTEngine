//
// Created by Kurt Slagle on 1/12/25.
//

#pragma once
#include <imgui.h>
#include <imgui-SFML.h>

inline bool EditImGuiVector2f(const char *label, sf::Vector2f &v) {
    if (ImGui::BeginChild(label)) {
        // SHOULD be fine, because they are laid out
        // next to each other in memory
        if (ImGui::InputFloat2(label, &v.x)) {
            return true;
        }
    }
    return false;
}

namespace ImGuiColors {
    static constexpr ImVec4 BrightBlue = ImVec4(0.149, 0.988f, 0.953f, 1.f);
    static constexpr ImVec4 BrightPink = ImVec4(1.f, 0.f, 0.929f, 1.f);
    static constexpr ImVec4 MutedMagenta = ImVec4(0.808f, 0.22f, 0.812f, 1.f);
    static constexpr ImVec4 InfoGray = ImVec4(0.729f, 0.729f, 0.729f, 1.f);
    static constexpr ImVec4 DebugBlue = ImVec4(0.f, 0.627f, 0.839f, 1.f);
    static constexpr ImVec4 WarningYellow = ImVec4(1.f, 1.f, 0.f, 1.f);
    static constexpr ImVec4 ErrorOrange = ImVec4(1.f, 0.569f, 0.f, 1.f);
    static constexpr ImVec4 FatalRed = ImVec4(0.91f, 0.165f, 0.f, 1.f);
}
