#ifndef CUSTOM_ELEMENTS_HPP
#define CUSTOM_ELEMENTS_HPP

#include <vector>
#include <iostream>

#include "imgui.h"
#include "imgui_internal.h"

float ANIMATION_SPEED = 0.08F;

class ToggleButton {
    public:
        ToggleButton(const char* str_id, const char* label, bool* v) : id(str_id), label(label), toggle(v) {}

        // Renders a toggle switch
        void Render_switch() {
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            float height = ImGui::GetFrameHeight();
            float width = height * 1.55f;
            float radius = height * 0.50f;

            if (ImGui::InvisibleButton(id, ImVec2(width, height))) {
                *toggle = !*toggle;
            }

            float t = *toggle ? 1.0f : 0.0f;

            ImGuiContext& g = *ImGui::GetCurrentContext();
            if (g.LastActiveId == g.CurrentWindow->GetID(id)) {
                float t_anim = ImSaturate(g.LastActiveIdTimer / ANIMATION_SPEED);
                t = *toggle ? (t_anim) : (1.0f - t_anim);
            }

            ImU32 col_bg;
            if (ImGui::IsItemHovered()) {
                col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
            } else {
                col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));
            }

            draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
            draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

            ImGui::SameLine();

            ImGui::Text("%s is set to %s", label, (toggle ? "ON" : "OFF"));
        }

    private:
        bool* toggle;
        const char* id;
        const char* label;
};

class MultiToggle {
    public:
        MultiToggle(int* current_pos,std::vector<char*> options, const char* id, const char* label) 
            : current_pos(current_pos), options(options), id(id), label(label) {}

        void Render() {
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            float height = ImGui::GetFrameHeight();
            float width = 2 * (height * 1.55f);
            float radius = height * 0.50f;
            float segment_width = width / options.size();

            ImGui::InvisibleButton(id, ImVec2(width, height));
            bool is_active = ImGui::IsItemActive();
            bool is_hovered = ImGui::IsItemHovered();

            if (is_active) {
                float mouse_x = ImGui::GetIO().MousePos.x;
                float relative_x = mouse_x - p.x;

                int new_pos = static_cast<int>(relative_x / segment_width);
                new_pos = ImClamp(new_pos, 0, static_cast<int>(options.size()) - 1);
                *current_pos = new_pos;
            }

            float t = *current_pos / static_cast<float>(options.size() - 1);

            ImU32 col_bg = ImGui::IsItemHovered()
                ? ImGui::GetColorU32(ImLerp(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.3f, 0.8f, 0.3f, 1.0f), t))
                : ImGui::GetColorU32(ImLerp(ImVec4(0.9f, 0.9f, 0.9f, 1.0f), ImVec4(0.6f, 0.7f, 0.3f, 1.0f), t));

            if (colors.size() > 0 && colors.size() == options.size()) {
                col_bg = colors.at(*current_pos);
            }

            draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
            draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
            ImGui::SameLine();

            ImGui::Text("%s: %s", label, options.at(*current_pos));
        }

        void SetColors(std::vector<ImU32> cols) { colors = cols; }

    private:
        std::vector<char*> options;
        std::vector<ImU32> colors;
        int* current_pos;
        const char* id;
        const char* label;
};

#endif