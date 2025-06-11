//
// Created by Kurt Slagle on 6/7/25.
//

#include "LightPlayer2.h"
#include <Editor/ImGuiHelpers.h>
#include <Misc/IconsFontAwesome6.h>

bool LightPlayer2::ShowEditor() {
    bool edited = false;
    unsigned int newPattIter = patternIter;
    EditorBeginRoundedChild("Pattern Data", "Patterns");
    if (ImGui::BeginTable("Pattern Data",
                          6,
                          ImGuiTableFlags_Resizable |
                          ImGuiTableFlags_BordersOuter |
                          ImGuiTableFlags_ScrollY, ImVec2(0.f, 300.f))) {
        ImGui::TableSetupColumn("Play");
        ImGui::TableSetupColumn("Func index");
        ImGui::TableSetupColumn("Step pause");
        ImGui::TableSetupColumn("Param");
        ImGui::TableSetupColumn("Param (Hex)");
        ImGui::TableSetupColumn("Name");
        ImGui::TableHeadersRow();
        for (unsigned int i = 0; i < numPatterns; i++) {
            ImGui::TableNextRow();

            const auto &p = pattData[i];
            if (i == patternIter) {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0,
                                       ImColor(255, 255, 0));
            }
            ImColor tColor = i == patternIter
                                 ? ImColor(0, 0, 0)
                                 : ImColor(255, 255, 255);
            ImGui::TableSetColumnIndex(0);
            ImGui::PushID(i);
            ImGui::SetNextItemWidth(25.f);
            if (ImGui::Button(ICON_FA_PLAY, ImVec2(15, 15))) {
                newPattIter = i;
                edited = true;
            }
            ImGui::PopID();
            ImGui::TableSetColumnIndex(1);
            ImGui::TextColored(tColor, "%u", p.funcIndex);
            ImGui::TableSetColumnIndex(2);
            ImGui::TextColored(tColor, "%u", p.stepPause);
            ImGui::TableSetColumnIndex(3);
            ImGui::TextColored(tColor, "%u", p.param);
            ImGui::TableSetColumnIndex(4);
            ImGui::TextColored(tColor,
                               "%u|%u",
                               getUpperBitsValue(p.param, 8),
                               getLowerBitsValue(p.param, 8));
            ImGui::TableSetColumnIndex(5);
            ImGui::TextColored(tColor, "%s", PatternNames[p.funcIndex]);
        }
        ImGui::EndTable();
    }
    EditorEndRoundedChild();
    if (edited) {
        if (newPattIter != patternIter) {
            patternIter = newPattIter;
            stepIter = 0;
            stepTimer = 0;
        }
    }
    return edited;
}
