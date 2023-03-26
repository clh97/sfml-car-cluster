#pragma once

#include <string>
#include "../imgui.h"

struct ClusterIcon {
    std::string name;
    std::string path;
    GLuint texture;
    ImVec2 size;
    ImVec2 position;
    ImVec4 color;
};

static void DrawClusterIcon(ClusterIcon &icon, float delta_time) {
    ImGui::GetWindowDrawList()->AddImage((void *)(intptr_t)icon.texture, icon.position, ImVec2(icon.position.x + icon.size.x, icon.position.y + icon.size.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::ColorConvertFloat4ToU32(icon.color));
}
