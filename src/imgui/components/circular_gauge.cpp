#pragma once
#include <cmath>
#include <memory>

#include "../imgui.h"

void DrawCircularGauge(const ImVec2 &center, float radius, float value, const char *label = nullptr)
    {
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        ImVec4 bg_color = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
        ImVec4 fg_color = ImVec4(0.0f, 0.7f, 0.0f, 1.0f);
        ImVec4 needle_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        ImVec4 text_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        int num_ticks = 10;
        float start_angle = 135.0f;
        float end_angle = -135.0f;
        float angle_range = end_angle - start_angle;
        float min_value = 0.0f;
        float max_value = 1.0f;

        // Draw background circle
        draw_list->AddCircle(center, radius, ImGui::ColorConvertFloat4ToU32(bg_color), 100);

        // Draw tick marks
        for (int i = 0; i <= num_ticks; ++i)
        {
            float angle = start_angle + (angle_range / num_ticks) * i;
            ImVec2 tick_start = ImVec2(center.x + radius * cosf(angle * M_PI / 180.0f), center.y + radius * sinf(angle * M_PI / 180.0f));
            ImVec2 tick_end = ImVec2(center.x + (radius - 10) * cosf(angle * M_PI / 180.0f), center.y + (radius - 10) * sinf(angle * M_PI / 180.0f));
            draw_list->AddLine(tick_start, tick_end, ImGui::ColorConvertFloat4ToU32(fg_color), 2.0f);
        }

        // Draw needle
        float value_angle = start_angle + angle_range * ((value - min_value) / (max_value - min_value));
        ImVec2 needle_end = ImVec2(center.x + (radius - 20) * cosf(value_angle * M_PI / 180.0f), center.y + (radius - 20) * sinf(value_angle * M_PI / 180.0f));
        draw_list->AddLine(center, needle_end, ImGui::ColorConvertFloat4ToU32(needle_color), 4.0f);

        // Draw label
        if (label)
        {
            ImVec2 label_size = ImGui::CalcTextSize(label);
            ImVec2 label_pos = ImVec2(center.x - label_size.x / 2.0f, center.y - label_size.y / 2.0f);
            ImGui::SetCursorScreenPos(label_pos);
            ImGui::TextColored(text_color, "%s", label);
        }
    }
