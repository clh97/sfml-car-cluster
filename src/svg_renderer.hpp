#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>

#include "imgui/imgui.h"

class SVGRenderer
{
public:
    SVGRenderer();
    ~SVGRenderer();
    SDL_Texture * renderSVG(const std::string &svg, const ImVec2 &size, const ImVec2 &position, const ImVec4 &color, SDL_Renderer* &renderer);

private:
    NSVGrasterizer *rast;
};
