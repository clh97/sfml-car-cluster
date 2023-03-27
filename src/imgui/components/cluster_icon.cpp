#pragma once

#include <string>
#include "../imgui.h"
#include "../imgui_stdlib.h"

struct ClusterIcon
{
    std::string name;
    std::string path;
    GLuint texture;
    ImVec2 size;
    ImVec2 position;
    ImVec4 color;
};

static void DrawClusterIcon(ClusterIcon &icon, float delta_time)
{
    ImGui::GetWindowDrawList()->AddImage((void *)(intptr_t)icon.texture, icon.position, ImVec2(icon.position.x + icon.size.x, icon.position.y + icon.size.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::ColorConvertFloat4ToU32(icon.color));
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
