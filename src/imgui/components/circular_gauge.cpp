#pragma once

#include <cmath>
#include <memory>

#include "../imgui.h"

struct CircularGauge
{
    ImVec2 center;
    float radius;
    float value;
    const char *label;
    ImVec4 bg_color;
    ImVec4 fg_color;
    ImVec4 needle_color;
    ImVec4 text_color;
    int num_ticks;
    float start_angle;
    float end_angle;
    float angle_range;
    float min_value;
    float max_value;
};

static void DrawCircularGauge(CircularGauge &gauge)
{
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    // Draw background circle
    draw_list->AddCircle(gauge.center, gauge.radius, ImGui::ColorConvertFloat4ToU32(gauge.bg_color), 100);

    // Draw tick marks
    for (int i = 0; i <= gauge.num_ticks; ++i)
    {
        float angle = gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
        ImVec2 tick_start = ImVec2(gauge.center.x + gauge.radius * cosf(angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(angle * M_PI / 180.0f));
        ImVec2 tick_end = ImVec2(gauge.center.x + (gauge.radius - 10) * cosf(angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 10) * sinf(angle * M_PI / 180.0f));
        draw_list->AddLine(tick_start, tick_end, ImGui::ColorConvertFloat4ToU32(gauge.fg_color), 2.0f);
    }

    // Draw needle
    float value_angle = gauge.start_angle + gauge.angle_range * ((gauge.value - gauge.min_value) / (gauge.max_value - gauge.min_value));
    ImVec2 needle_end = ImVec2(gauge.center.x + (gauge.radius - 20) * cosf(value_angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 20) * sinf(value_angle * M_PI / 180.0f));
    draw_list->AddLine(gauge.center, needle_end, ImGui::ColorConvertFloat4ToU32(gauge.needle_color), 4.0f);

    // Draw label
    if (gauge.label)
    {
        ImVec2 label_size = ImGui::CalcTextSize(gauge.label);
        ImVec2 label_pos = ImVec2(gauge.center.x - label_size.x / 2.0f, gauge.center.y - label_size.y / 2.0f);
        ImGui::SetCursorScreenPos(label_pos);
        ImGui::TextColored(gauge.text_color, "%s", gauge.label);
    }
}
