#include <string>

#include "constants.hpp"
#include "platform.hpp"
#include "cluster_data.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
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

protected:
    bool is_running = false;
    float last_frame_time = 0.0f;
    float current_frame_time = 0.0f;
    float delta_time = 0.0f;
    float last_delta_time = 0.0f;
    float total_elapsed_time = 0.0f;
    float fps = 0.0f;
    int frame_count = 0;
};

class ImGuiApplication : public Application
{
public:
    ImGuiApplication(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height);
    ~ImGuiApplication();

    void Run() override;

    void Update() override;

    void Render() override;

private:
    ClusterData cluster_data;
};
