#include "application.hpp"

#include "imgui/components/circular_gauge.cpp"

#include <iostream>

Application::Application(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height)
    : m_adapter(std::move(adapter))
{
    m_window = m_adapter->CreateWindow(title, width, height);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_adapter->SetCurrentContext(m_window);
    SDL_GL_CreateContext(m_window);

    glViewport(0, 0, width, height);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Application::~Application()
{
    m_adapter->DestroyWindow(m_window);
}

ImGuiApplication::ImGuiApplication(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height)
    : Application(std::move(adapter), title, width, height)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.DisplaySize.x = width;
    io.DisplaySize.y = height;
    io.WantSaveIniSettings = false;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(m_window, SDL_GL_GetCurrentContext());
    ImGui_ImplOpenGL3_Init("#version 330");
}

ImGuiApplication::~ImGuiApplication()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiApplication::Run()
{
    bool is_running = true;
    while (is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
        }

        Update();
        Render();

        m_adapter->SwapBuffers(m_window);
    }
}

void ImGuiApplication::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiApplication::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    bool is_open = true;
    ImGui::Begin("Gauge", &is_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav);

    SDL_Point window_size = m_adapter->GetWindowSize(m_window);

    ImGui::SetWindowSize(ImVec2(window_size.x, window_size.y));

    DrawCircularGauge(ImVec2(200, 200), 100, 0.5f, 0.0f, 1.0f);

    // ImGui::ShowDemoWindow();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glFlush();
}
