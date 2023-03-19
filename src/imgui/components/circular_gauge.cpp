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
    struct
    {
        int min;
        int max;
    } range_limits;
};

static void DrawCircularGauge(CircularGauge &gauge)
{
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    // Draw background circle
    draw_list->AddCircle(gauge.center, gauge.radius, ImGui::ColorConvertFloat4ToU32(gauge.bg_color), gauge.radius);

    // Draw outline circle
    draw_list->AddCircle(gauge.center, gauge.radius, ImGui::ColorConvertFloat4ToU32(gauge.fg_color), gauge.radius, 2.0f);

    // Hide bottom part of gauge
    static const ImVec4 bottom_part = ImVec4(
        gauge.center.x + gauge.radius * cosf(135.0f * M_PI / 180.0f),
        gauge.center.y + gauge.radius,
        gauge.center.x + gauge.radius * cosf(45.0f * M_PI / 180.0f),
        gauge.center.y + gauge.radius * sinf(45.0f * M_PI / 180.0f));
    draw_list->AddRectFilled(
        ImVec2(bottom_part.x, bottom_part.y),
        ImVec2(bottom_part.z, bottom_part.w),
        ImGui::ColorConvertFloat4ToU32(gauge.bg_color),
        1.0f);

    // Draw tick marks
    float tick_value_interval = (gauge.max_value - gauge.min_value) / 10;
    for (int i = 0; i <= gauge.num_ticks; ++i)
    {
        float angle = gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
        ImVec2 tick_start = ImVec2(gauge.center.x + gauge.radius * cosf(angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(angle * M_PI / 180.0f));
        ImVec2 tick_end = ImVec2(gauge.center.x + (gauge.radius - 20) * cosf(angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 20) * sinf(angle * M_PI / 180.0f));
        draw_list->AddLine(tick_start, tick_end, ImGui::ColorConvertFloat4ToU32(gauge.fg_color), 2.0f);

        // Add smaller ticks between main ticks
        if (i < gauge.num_ticks)
        {
            float small_angle_step = (gauge.angle_range / gauge.num_ticks) / 5;
            for (int j = 1; j <= 5; ++j)
            {
                float small_angle = angle + small_angle_step * j;
                ImVec2 small_tick_start = ImVec2(gauge.center.x + gauge.radius * cosf(small_angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(small_angle * M_PI / 180.0f));
                ImVec2 small_tick_end = ImVec2(gauge.center.x + (gauge.radius - 12) * cosf(small_angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 12) * sinf(small_angle * M_PI / 180.0f));
                draw_list->AddLine(small_tick_start, small_tick_end, ImGui::ColorConvertFloat4ToU32(gauge.fg_color), 1.0f);
            }
        }

        // Draw labels for main ticks
        if (i % (gauge.num_ticks / 10) == 0)
        {
            float label_value = std::round((gauge.range_limits.max / gauge.num_ticks) * i / 10.0f) * 10.0f;
            std::string label_text = fmt::format("{:.0f}", label_value);
            ImVec2 label_size = ImGui::CalcTextSize(label_text.c_str());
            float label_radius = gauge.radius * 0.8f;
            float theta = 90.f + gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
            ImVec2 label_pos = ImVec2(
                gauge.center.x + label_radius * std::sin(theta * M_PI / 180.0f),
                gauge.center.y - label_radius * std::cos(theta * M_PI / 180.0f));
            label_pos.x -= label_size.x / 2.0f;
            label_pos.y -= label_size.y / 2.0f;

            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
            ImGui::SetCursorScreenPos(label_pos);
            ImGui::TextColored(gauge.text_color, "%s", label_text.c_str());
            ImGui::PopFont();
        }
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
