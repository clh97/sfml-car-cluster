#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <fmt/format.h>
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>

#include "imgui/imgui.h"

class SVGRenderer
{
public:
    SVGRenderer();
    ~SVGRenderer();
    GLuint renderSVG(const std::string svg_file_path, const ImVec2& size, const ImVec2& position, const ImVec4& color, SDL_GLContext& gl_context);

private:
    NSVGrasterizer *rast;
};
