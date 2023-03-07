#pragma once

#include <fmt/format.h>
#include <SDL2/SDL.h>

#if defined(__APPLE__)
#include <SDL2/SDL_opengl.h>
#else
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
};

class OpenGLAdapter : public PlatformAdapter
{
public:
    SDL_Window *CreateWindow(const char *title, int width, int height) override
    {
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, window_flags);
    }

    void DestroyWindow(SDL_Window *window) override
    {
        SDL_DestroyWindow(window);
    }

    void SetCurrentContext(SDL_Window *window) override
    {
        SDL_GL_MakeCurrent(window, gl_context_);
    }

    void SwapBuffers(SDL_Window *window) override
    {
        SDL_GL_SwapWindow(window);
    }

private:
    SDL_GLContext gl_context_;
};

// class VulkanAdapter : public PlatformAdapter
// {
// public:
//     SDL_Window *CreateWindow(const char *title, int width, int height) override
//     {
//         SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);
//         SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
//         SDL_Vulkan_CreateSurface(window, SDL_Vulkan_GetVkInstance(), &surface_);
//         return window;
//     }

//     void DestroyWindow(SDL_Window *window) override
//     {
//         SDL_Vulkan_DestroySurface(window, surface_);
//         SDL_DestroyWindow(window);
//     }

//     void SetCurrentContext(SDL_Window *window) override
//     {
//         // no-op
//     }

//     void SwapBuffers(SDL_Window *window) override
//     {
//         // no-op
//     }

// private:
//     VkSurfaceKHR surface_;
// };
