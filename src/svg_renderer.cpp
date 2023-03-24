#include "svg_renderer.hpp"

SVGRenderer::SVGRenderer()
{
    rast = nsvgCreateRasterizer();
}

SVGRenderer::~SVGRenderer()
{
    nsvgDeleteRasterizer(rast);
}

SDL_Texture * SVGRenderer::renderSVG(const std::string &svg, const ImVec2 &size, const ImVec2 &position, const ImVec4 &color, SDL_Renderer* &renderer)
{
    NSVGimage *image = nsvgParse((char *)svg.c_str(), "px", 96);
    if (image == NULL)
    {
        fmt::print("Error parsing SVG data.\n");
        return NULL;
    }

    int img_width = (int)image->width;
    int img_height = (int)image->height;
    unsigned char *img_data = new unsigned char[img_width * img_height * 4];
    nsvgRasterize(rast, image, 0, 0, 1, img_data, img_width, img_height, img_width * 4);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, img_width, img_height);
    SDL_UpdateTexture(texture, NULL, img_data, img_width * 4);

    delete[] img_data;
    nsvgDelete(image);

    return texture;
}

