#pragma once

#include <string>

#include "../imgui.h"
#include "../imgui_stdlib.h"

struct ClusterIcon
{
    std::string name;
    std::string path;
    unsigned int texture;
    ImVec2 size;
    ImVec2 position;
    ImVec4 color;
};

struct ClusterLightIndicator
{
    bool on = false;
    ClusterIcon icon;
    ImVec4 color_on = THEME_COLOR_LIGHT_GRAY;
    ImVec4 color_off = THEME_COLOR_YELLOW;
};

static void DrawClusterIcon(ClusterLightIndicator cli, float delta_time)
{
    ImU32 color = ImGui::ColorConvertFloat4ToU32(cli.icon.color);

    if (cli.on)
    {
        color = ImGui::ColorConvertFloat4ToU32(cli.color_on);
    }
    else
    {
        color = ImGui::ColorConvertFloat4ToU32(cli.color_off);
    }


    ImGui::GetWindowDrawList()->AddImage(
        (void *)(intptr_t)cli.icon.texture,
        cli.icon.position,
        ImVec2(cli.icon.position.x + cli.icon.size.x, cli.icon.position.y + cli.icon.size.y),
        ImVec2(0, 0), ImVec2(1, 1),
        ImGui::ColorConvertFloat4ToU32(cli.icon.color)
    );
}

static void DrawClusterIconEditor(ClusterIcon &icon, std::string title, float delta_time)
{
    if (ImGui::CollapsingHeader(title.c_str()))
    {
        ImGui::BeginChild(std::string("Cluster Icon Editor - " + title).c_str(), ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("Name");
        ImGui::InputText("##name", &icon.name);
        ImGui::Text("Path");
        ImGui::InputText("##path", &icon.path);
        ImGui::Text("Size");
        ImGui::InputFloat2("##size", &icon.size.x);
        ImGui::Text("Position");
        ImGui::InputFloat2("##position", &icon.position.x);
        ImGui::Text("Color");
        ImGui::ColorEdit4("##color", &icon.color.x);
        ImGui::EndChild();
    }
}
