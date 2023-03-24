#pragma once

#include <string>
#include "../imgui.h"

struct ClusterIcon {
    std::string name;
    std::string path;
    ImVec2 size;
    ImVec2 uv0;
    ImVec2 uv1;
    ImVec4 tint_col;
    ImVec4 border_col;
};

