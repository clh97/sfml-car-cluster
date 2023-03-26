#pragma once

#include <fmt/format.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#ifndef __APPLE__
#include <SDL2/SDL_vulkan.h>
#endif


class PlatformAdapter
{
public:
    virtual ~PlatformAdapter() = default;

    virtual SDL_Window *CreateWindow(const char *title, int width, int height) = 0;
    virtual void DestroyWindow(SDL_Window *window) = 0;
    virtual void SetCurrentContext(SDL_Window *window) = 0;
    virtual void SwapBuffers(SDL_Window *window) = 0;

    SDL_Point GetWindowSize(SDL_Window *window);
};

class OpenGLAdapter : public PlatformAdapter
{
public:
    SDL_Window *CreateWindow(const char *title, int width, int height) override;

    void DestroyWindow(SDL_Window *window);
    void SetCurrentContext(SDL_Window *window);
    void SwapBuffers(SDL_Window *window);
private:
    SDL_GLContext gl_context_;
};
