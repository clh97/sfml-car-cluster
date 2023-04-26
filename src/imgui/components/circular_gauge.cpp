#pragma once

#include <fmt/format.h>
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
    bool hide_outline;
    bool hide_bottom;
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
    struct CriticalZone
    {
        bool enabled;
        float start_percent;
        ImVec4 color;
    } critical_zone;
};

static void DrawCircularGauge(CircularGauge &gauge, float delta_time)
{
    int critical_zone_start_tick_idx = static_cast<int>(std::round(gauge.num_ticks * gauge.critical_zone.start_percent));
    float critical_zone_start_angle = gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * critical_zone_start_tick_idx;

    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    if (gauge.value > gauge.max_value)
    {
        gauge.value = gauge.max_value;
    }
    else if (gauge.value < gauge.min_value)
    {
        gauge.value = gauge.min_value;
    }

    // Draw background circle
    draw_list->AddCircleFilled(gauge.center, gauge.radius, ImGui::ColorConvertFloat4ToU32(gauge.bg_color), gauge.radius);

    if (!gauge.hide_outline)
    {
        // Draw outline circle composed by 256 lines
        const int num_segments = 256;
        const float angle_step = gauge.angle_range / static_cast<float>(num_segments);
        for (int i = 0; i <= num_segments; ++i)
        {
            float angle = gauge.start_angle + angle_step * i;
            float angle_next = gauge.start_angle + angle_step * (i + 1);

            ImVec2 line_start = ImVec2(gauge.center.x + gauge.radius * cosf(angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(angle * M_PI / 180.0f));
            ImVec2 line_end = ImVec2(gauge.center.x + gauge.radius * cosf(angle_next * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(angle_next * M_PI / 180.0f));
            ImVec4 line_color = gauge.fg_color;

            if (angle >= critical_zone_start_angle && gauge.critical_zone.enabled)
            {
                line_color = gauge.critical_zone.color;
            }

            draw_list->AddLine(
                line_start,
                line_end,
                ImGui::ColorConvertFloat4ToU32(line_color));
        }
    }

    // Draw tick marks
    float tick_value_interval = (gauge.max_value - gauge.min_value) / 10;

    for (int i = 0; i <= gauge.num_ticks; ++i)
    {
        // Red zone
        ImVec4 tick_color = gauge.fg_color;
        float angle = gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
        if (angle >= critical_zone_start_angle && gauge.critical_zone.enabled)
        {
            tick_color = gauge.critical_zone.color;
        }

        // Draw main ticks
        // float angle = gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
        ImVec2 tick_start = ImVec2(gauge.center.x + gauge.radius * cosf(angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(angle * M_PI / 180.0f));
        ImVec2 tick_end = ImVec2(gauge.center.x + (gauge.radius - 20) * cosf(angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 20) * sinf(angle * M_PI / 180.0f));
        draw_list->AddLine(tick_start, tick_end, ImGui::ColorConvertFloat4ToU32(tick_color), 2.0f);

        // Add smaller ticks between main ticks
        if (i < gauge.num_ticks)
        {
            float small_angle_step = (gauge.angle_range / gauge.num_ticks) / 5;
            for (int j = 1; j <= 5; ++j)
            {
                float small_angle = angle + small_angle_step * j;
                ImVec2 small_tick_start = ImVec2(gauge.center.x + gauge.radius * cosf(small_angle * M_PI / 180.0f), gauge.center.y + gauge.radius * sinf(small_angle * M_PI / 180.0f));
                ImVec2 small_tick_end = ImVec2(gauge.center.x + (gauge.radius - 12) * cosf(small_angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 12) * sinf(small_angle * M_PI / 180.0f));
                draw_list->AddLine(small_tick_start, small_tick_end, ImGui::ColorConvertFloat4ToU32(tick_color), 1.0f);
            }
        }

        // Draw labels for main ticks
        float label_value = std::ceil((gauge.range_limits.max / gauge.num_ticks) * i);
        std::string label_text = fmt::format("{:.0f}", label_value);
        ImVec2 label_size = ImGui::CalcTextSize(label_text.c_str());
        float label_radius = gauge.radius * 0.78f;
        float theta = 90.f + gauge.start_angle + (gauge.angle_range / gauge.num_ticks) * i;
        ImVec2 label_pos = ImVec2(
            gauge.center.x + label_radius * std::sin(theta * M_PI / 180.0f),
            gauge.center.y - label_radius * std::cos(theta * M_PI / 180.0f));
        label_pos.x -= label_size.x / 2.0f;
        label_pos.y -= label_size.y / 2.0f;
        ImGui::SetCursorScreenPos(label_pos);
        draw_list->AddText(label_pos, ImGui::ColorConvertFloat4ToU32(gauge.text_color), label_text.c_str());
    }

    // Draw needle
    float needle_angle = gauge.start_angle + (gauge.angle_range / (gauge.max_value - gauge.min_value)) * (gauge.value - gauge.min_value);
    ImVec2 needle_start = ImVec2(gauge.center.x + gauge.radius / 4 * cosf(needle_angle * M_PI / 180.0f), gauge.center.y + gauge.radius / 4 * sinf(needle_angle * M_PI / 180.0f));
    ImVec2 needle_end = ImVec2(gauge.center.x + (gauge.radius - 20) * cosf(needle_angle * M_PI / 180.0f), gauge.center.y + (gauge.radius - 20) * sinf(needle_angle * M_PI / 180.0f));
    draw_list->AddLine(needle_start, needle_end, ImGui::ColorConvertFloat4ToU32(gauge.needle_color), 4.0f);

    // Draw label
    if (gauge.label.length() > 0)
    {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
        ImVec2 label_size = ImGui::CalcTextSize(gauge.label.c_str());
        ImVec2 label_pos = ImVec2(gauge.center.x - label_size.x / 2.0f, gauge.center.y - label_size.y / 2.0f);

        draw_list->AddText(label_pos, ImGui::ColorConvertFloat4ToU32(gauge.text_color), gauge.label.c_str());
        ImGui::PopFont();
    }
}

static void DrawCircularGaugeEditor(CircularGauge &gauge, std::string title)
{
    // ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_None);
    if (ImGui::CollapsingHeader(title.c_str()))
    {
        ImGui::BeginChild(std::string("Circular Gauge Editor - " + title).c_str());
        ImGui::Text("Center");
        ImGui::DragFloat2("##Center", &gauge.center.x, 1.0f);

        ImGui::Text("Radius");
        ImGui::DragFloat("##Radius", &gauge.radius, 1.0f);

        ImGui::Text("Value");
        ImGui::DragFloat("##Value", &gauge.value, 0.01f);

        ImGui::Text("Label");
        static char label[256] = "";
        strncpy(label, gauge.label.c_str(), sizeof(label));
        if (ImGui::InputText("##Label", label, sizeof(label)))
        {
            gauge.label = label;
        }

        ImGui::Text("Background Color");
        ImGui::ColorEdit4("##BGColor", (float *)&gauge.bg_color);

        ImGui::Text("Foreground Color");
        ImGui::ColorEdit4("##FGColor", (float *)&gauge.fg_color);

        ImGui::Text("Needle Color");
        ImGui::ColorEdit4("##NeedleColor", (float *)&gauge.needle_color);

        ImGui::Text("Text Color");
        ImGui::ColorEdit4("##TextColor", (float *)&gauge.text_color);

        ImGui::Text("Hide Outline");
        ImGui::Checkbox("##HideOutline", &gauge.hide_outline);

        ImGui::Text("Hide Bottom");
        ImGui::Checkbox("##HideBottom", &gauge.hide_bottom);

        ImGui::Text("Number of Ticks");
        ImGui::DragInt("##NumTicks", &gauge.num_ticks, 1.0f, 0, 100);

        ImGui::Text("Start Angle");
        ImGui::DragFloat("##StartAngle", &gauge.start_angle, 1.0f, -360.0f, 360.0f);

        ImGui::Text("End Angle");
        ImGui::DragFloat("##EndAngle", &gauge.end_angle, 1.0f, -360.0f, 360.0f);

        ImGui::Text("Angle Range");
        ImGui::DragFloat("##AngleRange", &gauge.angle_range, 1.0f, 0.0f, 360.0f);

        ImGui::Text("Min Value");
        ImGui::DragFloat("##MinValue", &gauge.min_value, 0.01f);

        ImGui::Text("Max Value");
        ImGui::DragFloat("##MaxValue", &gauge.max_value, 0.01f);

        ImGui::Text("Range Limits");
        ImGui::DragInt("##RangeLimitsMin", &gauge.range_limits.min, 1.0f);
        ImGui::DragInt("##RangeLimitsMax", &gauge.range_limits.max, 1.0f);

        ImGui::Text("Critical Zone");
        ImGui::Checkbox("##CriticalZoneEnabled", &gauge.critical_zone.enabled);
        ImGui::SameLine();
        ImGui::Text("Enabled");
        ImGui::DragFloat("##CriticalZoneStartPercent", &gauge.critical_zone.start_percent, 0.01f, 0.0f, 100.0f);
        ImGui::SameLine();
        ImGui::Text("Start Percent");
        ImGui::ColorEdit4("##CriticalZoneColor", (float *)&gauge.critical_zone.color);
        ImGui::EndChild();
    }
}
