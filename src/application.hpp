#pragma once
#include <cmath>

#include "platform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"

class Application
{
public:
    SDL_Window *m_window;
    std::unique_ptr<PlatformAdapter> m_adapter;

    Application(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height);

    ~Application();

    virtual void Run() = 0;

    virtual void Update() = 0;

    virtual void Render() = 0;
};

class ImGuiApplication : public Application
{
public:
    ImGuiApplication(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height);
    ~ImGuiApplication();

    void Run() override;

    void Update() override;

    void Render() override;
};
