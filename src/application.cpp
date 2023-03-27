#include "application.hpp"
#include "svg_renderer.hpp"

#include "interpolation.cpp"
#include "imgui/components/circular_gauge.cpp"
#include "imgui/components/cluster_icon.cpp"

Application::Application(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height)
    : m_adapter(std::move(adapter))
{
    m_window = m_adapter->CreateWindow(title, width, height);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetSwapInterval(-1);

    m_adapter->SetCurrentContext(m_window);
    SDL_GL_CreateContext(m_window);

    glViewport(0, 0, width, height);

    // fmt::print("OpenGL version: {}\n", std::string(glGetString(GL_VERSION)));
    // fmt::print("GLSL version: {}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    // fmt::print("Vendor: {}\n", glGetString(GL_VENDOR));
    // fmt::print("Renderer: {}\n", glGetString(GL_RENDERER));
}

Application::~Application()
{
    m_adapter->DestroyWindow(m_window);
}

InstrumentClusterApplication::InstrumentClusterApplication(std::unique_ptr<PlatformAdapter> adapter, std::unique_ptr<ClusterData> _cluster_data, const char *title, int width, int height)
    : Application(std::move(adapter), title, width, height), m_cluster_data(std::move(_cluster_data))
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();

    ImFontConfig config;
    // config.SizePixels = 24.0f;
    io.Fonts->AddFontFromFileTTF("../src/assets/OpenSans-Medium.ttf", 14.0f, &config);
    io.Fonts->AddFontFromFileTTF("../src/assets/OpenSans-Medium.ttf", 18.0f, &config);
    io.Fonts->AddFontFromFileTTF("../src/assets/OpenSans-Medium.ttf", 24.0f, &config);
    io.Fonts->AddFontFromFileTTF("../src/assets/OpenSans-Medium.ttf", 32.0f, &config);
    io.DisplaySize.x = width;
    io.DisplaySize.y = height;
    io.WantSaveIniSettings = false;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(m_window, SDL_GL_GetCurrentContext());
    ImGui_ImplOpenGL3_Init("#version 330");

    // Load textures
    SVGRenderer svg_renderer;
    SDL_GLContext gl_context = SDL_GL_GetCurrentContext();

    fmt::print("Loading textures...\n");
    m_cluster_data->hand_brake.icon.texture = svg_renderer.renderSVG(
        m_cluster_data->hand_brake.icon.path,
        m_cluster_data->hand_brake.icon.size,
        m_cluster_data->hand_brake.icon.position,
        m_cluster_data->hand_brake.icon.color,
        gl_context);

    m_cluster_data->headlights.icon.texture = svg_renderer.renderSVG(
        m_cluster_data->headlights.icon.path,
        m_cluster_data->headlights.icon.size,
        m_cluster_data->headlights.icon.position,
        m_cluster_data->headlights.icon.color,
        gl_context);

    m_cluster_data->wipers.icon.texture = svg_renderer.renderSVG(
        m_cluster_data->wipers.icon.path,
        m_cluster_data->wipers.icon.size,
        m_cluster_data->wipers.icon.position,
        m_cluster_data->wipers.icon.color,
        gl_context);

    m_cluster_data->arrow_left.icon.texture = svg_renderer.renderSVG(
        m_cluster_data->arrow_left.icon.path,
        m_cluster_data->arrow_left.icon.size,
        m_cluster_data->arrow_left.icon.position,
        m_cluster_data->arrow_left.icon.color,
        gl_context);

    m_cluster_data->arrow_right.icon.texture = svg_renderer.renderSVG(
        m_cluster_data->arrow_right.icon.path,
        m_cluster_data->arrow_right.icon.size,
        m_cluster_data->arrow_right.icon.position,
        m_cluster_data->arrow_right.icon.color,
        gl_context);

    delta_time = 0.0f;
}

InstrumentClusterApplication::~InstrumentClusterApplication()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void InstrumentClusterApplication::Run()
{
    is_running = true;

    last_frame_time = SDL_GetTicks() / 1000.0f;

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

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_running = false;
                }

                if (event.key.keysym.sym == SDLK_F3)
                {
                    show_editor = !show_editor;
                }
            }
        }

        current_frame_time = SDL_GetTicks() / 1000.0f;
        delta_time = current_frame_time - last_frame_time;
        fps = 1.0f / delta_time;
        last_delta_time = delta_time;
        last_frame_time = current_frame_time;
        frame_count++;

        Update();
        Render();

        SDL_Delay(1000 / MAX_FPS);
        m_adapter->SwapBuffers(m_window);
        total_elapsed_time += delta_time;
    }
}

void InstrumentClusterApplication::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void InstrumentClusterApplication::Render()
{
    SDL_Point window_size = m_adapter->GetWindowSize(m_window);
    bool is_open = true;

    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    {
        ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Gauge", &is_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav);

        if (show_editor)
        {
            ImGui::BeginChild("Editor", ImVec2(window_size.x / 2, window_size.y), true, ImGuiWindowFlags_NoBackground);
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

            /* Cluster data */
            ImGui::Text("Cluster data");
            ImGui::SliderFloat("Speed", &m_cluster_data->speedometer.kmh_speed, (float)m_cluster_data->speedometer.range.min, (float)m_cluster_data->speedometer.range.max, "%d km/h");
            ImGui::SliderFloat("RPM", &m_cluster_data->rpm.rpm, m_cluster_data->rpm.range.min, m_cluster_data->rpm.range.max, "%d RPM");
            ImGui::Checkbox("Hand brake", &m_cluster_data->hand_brake.engaged);
            ImGui::Checkbox("Headlights", &m_cluster_data->headlights.on);
            if (m_cluster_data->headlights.on) ImGui::Checkbox("Headlights high beam", &m_cluster_data->headlights.high_beam);
            ImGui::Checkbox("Wipers", &m_cluster_data->wipers.on);

            ImGui::Separator();

            ImGui::PopFont();
            ImGui::EndChild();
        }

        {
            ImGui::SameLine();
            // ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::BeginChild("Cluster", ImVec2(window_size.x, window_size.y), false);
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
            /* Draw gauges */
            DrawCircularGauge(m_cluster_data->speedometer.gauge, delta_time);
            DrawCircularGauge(m_cluster_data->rpm.gauge, delta_time);

            /* Draw icons */
            DrawClusterIcon(m_cluster_data->hand_brake.icon, delta_time);
            DrawClusterIcon(m_cluster_data->headlights.icon, delta_time);
            DrawClusterIcon(m_cluster_data->wipers.icon, delta_time);
            DrawClusterIcon(m_cluster_data->arrow_left.icon, delta_time);

            DrawClusterIcon(m_cluster_data->arrow_right.icon, delta_time);

            ImGui::PopFont();
            ImGui::EndChild();
        }
    }

    {
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glFlush();
    }
}
