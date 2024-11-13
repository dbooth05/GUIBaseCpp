#ifndef CUSTOM_ELEMENTS_HPP
#define CUSTOM_ELEMENTS_HPP

#include "imgui.h"
#include "imgui_internal.h"

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
            float ANIMATION_SPEED = 0.08f;
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

#endif