#ifndef LIGHT_H
#define LIGHT_H

#include<stdint.h>
#include <imgui.h>
#include <fmt/base.h>

class Light {
public:
    uint8_t r = 1, g = 2, b = 3;
    ImVec4 floats;

    void init(uint8_t Rd, uint8_t Gn, uint8_t Bu) {
        r = Rd;
        g = Gn;
        b = Bu;
    }

    void updateFloatsFromRGB() {
        floats = ImVec4(
                        r / 255.0f,
                        g / 255.0f,
                        b / 255.0f,
                        1.f
                       );
    }

    void updateRGBFromFloats() {
        r      = static_cast<uint8_t>(floats.x * 255.f);
        g      = static_cast<uint8_t>(floats.y * 255.f);
        b      = static_cast<uint8_t>(floats.z * 255.f);
    }

    Light(uint8_t Rd, uint8_t Gn, uint8_t Bu) {
        init(Rd, Gn, Bu);
        updateFloatsFromRGB();
    }

    Light() {
    }

    bool RenderEditor() {
        bool edited = false;
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.f);
        ImGui::PushID(this);
        if (ImGui::ColorEdit4("##Lt",
                              &floats.x,
                              ImGuiColorEditFlags_NoInputs |
                              ImGuiColorEditFlags_NoLabel)) {
            fmt::println("Changed light color to {} {} {}",
                         r,
                         g,
                         b);
            updateRGBFromFloats();
            edited = true;
        }
        ImGui::PopID();
        ImGui::PopStyleVar();
        return edited;
    }

    bool operator ==(const Light &Lt) const {
        if (r != Lt.r || g != Lt.g || b != Lt.b) return false;
        return true;
    }
};

#endif // LIGHT_H
