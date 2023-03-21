#pragma once

#include <cmath>
#include <memory>

#include "../../interpolation.cpp"
#include "../imgui.h"

struct CircularGauge
{
    ImVec2 center;
    float radius;
    float value;
    std::string label;
    ImVec4 bg_color;
    ImVec4 fg_color;
    ImVec4 needle_color;
    ImVec4 text_color;
    bool red_zone;
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

static void DrawCircularGauge(CircularGauge *gauge, float delta_time)
{
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    if (gauge->value > gauge->max_value)
    {
        gauge->value = gauge->max_value;
    }
    else if (gauge->value < gauge->min_value)
    {
        gauge->value = gauge->min_value;
    }

    // Draw background circle
    draw_list->AddCircleFilled(gauge->center, gauge->radius, ImGui::ColorConvertFloat4ToU32(gauge->bg_color), gauge->radius);

    // Draw ticks
    if (gauge->red_zone)
    { // Draw outline circle composed by 256 lines
        const int num_segments = 256;
const float angle_step = gauge->angle_range / num_segments;
for (int i = 0; i <= num_segments; ++i)
{
    float angle = gauge->start_angle + angle_step * i;
    float angle_next = gauge->start_angle + angle_step * (i + 1);

    ImVec2 line_start = ImVec2(gauge->center.x + (gauge->radius - 10) * cosf(angle * M_PI / 180.0f), gauge->center.y + (gauge->radius - 10) * sinf(angle * M_PI / 180.0f));
    ImVec2 line_end = ImVec2(gauge->center.x + (gauge->radius - 10) * cosf(angle_next * M_PI / 180.0f), gauge->center.y + (gauge->radius - 10) * sinf(angle_next * M_PI / 180.0f));

    if (std::ceil(num_segments * 0.8f) <= i)
    {
        draw_list->AddLine(
            line_start,
            line_end,
            ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)),
            2.0f);
    }
    else
    {
        draw_list->AddLine(
            line_start,
            line_end,
            ImGui::ColorConvertFloat4ToU32(gauge->fg_color),
            1.0f);
    }
}
    }
    else
    { // Draw simple outline circle
        draw_list->AddCircle(gauge->center, gauge->radius, ImGui::ColorConvertFloat4ToU32(gauge->fg_color), gauge->radius);
    }

    // Hide bottom part of gauge
    static const ImVec4 bottom_part = ImVec4(
        gauge->center.x + gauge->radius * cosf(135.0f * M_PI / 180.0f),
        gauge->center.y + gauge->radius,
        gauge->center.x + gauge->radius * cosf(45.0f * M_PI / 180.0f),
        gauge->center.y + gauge->radius * sinf(45.0f * M_PI / 180.0f)
    );

    draw_list->AddRectFilled(
        ImVec2(bottom_part.x, bottom_part.y),
        ImVec2(bottom_part.z, bottom_part.w),
        ImGui::ColorConvertFloat4ToU32(gauge->bg_color)
    );

    // Draw tick marks
    float tick_value_interval = (gauge->max_value - gauge->min_value) / 10;
    for (int i = 0; i <= gauge->num_ticks; ++i)
    {
        // Red zone
        ImVec4 tick_color = gauge->fg_color;
        if (i >= gauge->num_ticks * 0.8f && gauge->red_zone)
        {
            tick_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        // Draw main ticks
        float angle = gauge->start_angle + (gauge->angle_range / gauge->num_ticks) * i;
        ImVec2 tick_start = ImVec2(gauge->center.x + gauge->radius * cosf(angle * M_PI / 180.0f), gauge->center.y + gauge->radius * sinf(angle * M_PI / 180.0f));
        ImVec2 tick_end = ImVec2(gauge->center.x + (gauge->radius - 20) * cosf(angle * M_PI / 180.0f), gauge->center.y + (gauge->radius - 20) * sinf(angle * M_PI / 180.0f));
        draw_list->AddLine(tick_start, tick_end, ImGui::ColorConvertFloat4ToU32(tick_color), 2.0f);

        // Add smaller ticks between main ticks
        if (i < gauge->num_ticks)
        {
            float small_angle_step = (gauge->angle_range / gauge->num_ticks) / 5;
            for (int j = 1; j <= 5; ++j)
            {
                float small_angle = angle + small_angle_step * j;
                ImVec2 small_tick_start = ImVec2(gauge->center.x + gauge->radius * cosf(small_angle * M_PI / 180.0f), gauge->center.y + gauge->radius * sinf(small_angle * M_PI / 180.0f));
                ImVec2 small_tick_end = ImVec2(gauge->center.x + (gauge->radius - 12) * cosf(small_angle * M_PI / 180.0f), gauge->center.y + (gauge->radius - 12) * sinf(small_angle * M_PI / 180.0f));
                draw_list->AddLine(small_tick_start, small_tick_end, ImGui::ColorConvertFloat4ToU32(tick_color), 1.0f);
            }
        }

        // Draw labels for main ticks
        float label_value = std::ceil((gauge->range_limits.max / gauge->num_ticks) * i);
        std::string label_text = fmt::format("{:.0f}", label_value);
        ImVec2 label_size = ImGui::CalcTextSize(label_text.c_str());
        float label_radius = gauge->radius * 0.78f;
        float theta = 90.f + gauge->start_angle + (gauge->angle_range / gauge->num_ticks) * i;
        ImVec2 label_pos = ImVec2(
            gauge->center.x + label_radius * std::sin(theta * M_PI / 180.0f),
            gauge->center.y - label_radius * std::cos(theta * M_PI / 180.0f));
        label_pos.x -= label_size.x / 2.0f;
        label_pos.y -= label_size.y / 2.0f;
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        ImGui::SetCursorScreenPos(label_pos);
        ImGui::TextColored(gauge->text_color, "%s", label_text.c_str());
        ImGui::PopFont();
    }

    // Draw needle
    float needle_angle = gauge->start_angle + (gauge->angle_range / (gauge->max_value - gauge->min_value)) * (gauge->value - gauge->min_value);
    ImVec2 needle_start = ImVec2(gauge->center.x + gauge->radius / 4 * cosf(needle_angle * M_PI / 180.0f), gauge->center.y + gauge->radius / 4 * sinf(needle_angle * M_PI / 180.0f));
    ImVec2 needle_end = ImVec2(gauge->center.x + (gauge->radius - 20) * cosf(needle_angle * M_PI / 180.0f), gauge->center.y + (gauge->radius - 20) * sinf(needle_angle * M_PI / 180.0f));
    draw_list->AddLine(needle_start, needle_end, ImGui::ColorConvertFloat4ToU32(gauge->needle_color), 2.0f);

    // Draw label
    if (gauge->label.length() > 0)
    {
        fmt::print("Label: {}\n", gauge->label);
        ImVec2 label_size = ImGui::CalcTextSize(gauge->label.c_str());
        ImVec2 label_posa = ImVec2(gauge->center.x - label_size.x / 2.0f, gauge->center.y + gauge->radius * 0.8f + label_size.y / 2.0f);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        ImGui::SetCursorScreenPos(label_posa);
        ImGui::TextColored(gauge->text_color, "%s", gauge->label.c_str());
        ImGui::PopFont();
    }
}
