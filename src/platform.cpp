#include "platform.hpp"

SDL_Point PlatformAdapter::GetWindowSize(SDL_Window *window)
{
    SDL_Point size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return size;
}

SDL_Window * OpenGLAdapter::CreateWindow(const char *title, int width, int height)
{
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            width, height, window_flags);
}

void OpenGLAdapter::DestroyWindow(SDL_Window *window)
{
    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(window);
}

void OpenGLAdapter::SetCurrentContext(SDL_Window *window)
{
    SDL_GL_MakeCurrent(window, gl_context_);
}

void OpenGLAdapter::SwapBuffers(SDL_Window *window)
{
    SDL_GL_SwapWindow(window);
}
