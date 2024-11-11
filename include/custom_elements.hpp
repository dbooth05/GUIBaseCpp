#ifndef CUSTOM_ELEMENTS_HPP
#define CUSTOM_ELEMENTS_HPP

#include "imgui.h"

void ToggleButton(const char* str_id, bool* v) {

    ImVec2 p = ImGui::GetCursorPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float ht = ImGui::GetFrameHeight();
    float wd = ht * 1.55f;
    float rd = ht * 0.50f;

    if (ImGui::InvisibleButton(str_id, ImVec2(wd, ht))) {
        *v = !*v;
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered()) {
        col_bg = *v ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
    } else {
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
    }

    draw_list->AddRectFilled(p, ImVec2(p.x + wd, p.y + ht), col_bg, rd);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + wd - rd) : (p.x + rd), p.y + rd), rd - 1.5f, IM_COL32(255, 255, 255, 255));
}

#endif