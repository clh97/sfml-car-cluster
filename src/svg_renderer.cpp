#include "svg_renderer.hpp"

SVGRenderer::SVGRenderer()
{
    rast = nsvgCreateRasterizer();

    if (rast == NULL) {
        fmt::print("Failed to create rasterizer");
    }
}

SVGRenderer::~SVGRenderer()
{
    nsvgDeleteRasterizer(rast);
}

GLuint SVGRenderer::renderSVG(const std::string svg_file_path, const ImVec2& size, const ImVec2& position, const ImVec4& color, SDL_GLContext& gl_context) {
    NSVGimage* image = nsvgParseFromFile(svg_file_path.c_str(), "px", 96.0f);

    if (image == nullptr) {
        std::cerr << "Failed to load SVG file: " << svg_file_path << std::endl;
        return 0;
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float scale = std::min(size.x / image->width, size.y / image->height);

    unsigned char* buffer = new unsigned char[(int)size.x * (int)size.y * 4];
    nsvgRasterize(rast, image, 0, 0, scale, buffer, (int)size.x, (int)size.y, (int)size.x * 4);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)size.x, (int)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    glColor4f(color.x, color.y, color.z, color.w);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(position.x, position.y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(position.x + size.x, position.y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(position.x + size.x, position.y + size.y);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(position.x, position.y + size.y);
    glEnd();

    delete[] buffer;
    nsvgDelete(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}
