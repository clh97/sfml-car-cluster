#include "application.hpp"

#include "interpolation.cpp"
#include "imgui/components/circular_gauge.cpp"

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

ImGuiApplication::ImGuiApplication(std::unique_ptr<PlatformAdapter> adapter, const char *title, int width, int height)
    : Application(std::move(adapter), title, width, height)
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

    delta_time = 0.0f;
}

ImGuiApplication::~ImGuiApplication()
{
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiApplication::Run()
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
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav;
    ImGui::Begin("Gauge", &is_open, flags);

    ImGui::SetWindowPos(ImVec2(0, 0));

    SDL_Point window_size = m_adapter->GetWindowSize(m_window);

    ImGui::SetWindowSize(ImVec2(window_size.x, window_size.y));

    /* Instrument cluster components */

    /* Speedometer gauge */
    static ClusterData::Speedometer speedometer_data = ClusterData::Speedometer{
        .range = {0, 280},
        .format = "{} km/h",
        .kmh_speed = (total_elapsed_time * 10.f), // ECU info
        .gauge = {
            .label = fmt::format(speedometer_data.format, static_cast<int>(speedometer_data.kmh_speed)),
            .center = {
                static_cast<float>(window_size.x * 0.8),
                static_cast<float>(window_size.y * 0.5),
            },
            .radius = 250,
            .value = Interpolation::map_range(static_cast<float>(speedometer_data.kmh_speed), static_cast<float>(speedometer_data.range.min), static_cast<float>(speedometer_data.range.max), 0.0f, 1.0f),
            .bg_color = THEME_COLOR_TRANSPARENT,
            .fg_color = THEME_COLOR_WHITE,
            .needle_color = THEME_COLOR_BLUE_1,
            .text_color = THEME_COLOR_WHITE,
            .hide_outline = false,
            .hide_bottom = false,
            .num_ticks = 14,
            .start_angle = 135,
            .end_angle = 45,
            .angle_range = 270,
            .min_value = 0.0f,
            .max_value = 1.0f,
            .range_limits = {
                .min = speedometer_data.range.min,
                .max = speedometer_data.range.max,
            },
            .critical_zone = {
                .enabled = false,
                .start_percent = 0.9f,
                .color = THEME_COLOR_BLUE_1,
            }
        }
    };

    /* RPM gauge */
    static ClusterData::RPM rpm_data = ClusterData::RPM{
        .range = {0, 8000},
        .format = "{} RPM",
        .rpm = total_elapsed_time * 100.f, // ECU info
        .gauge = {
            .label = fmt::format(rpm_data.format, static_cast<int>(rpm_data.rpm)),
            .center = {
                static_cast<float>(window_size.x * 0.2),
                static_cast<float>(window_size.y * 0.5),
            },
            .radius = 250,
            .value = Interpolation::map_range(static_cast<float>(rpm_data.rpm), static_cast<float>(rpm_data.range.min), static_cast<float>(rpm_data.range.max), 0.0f, 1.0f),
            .bg_color = THEME_COLOR_TRANSPARENT,
            .fg_color = THEME_COLOR_WHITE,
            .needle_color = THEME_COLOR_BLUE_1,
            .text_color = THEME_COLOR_WHITE,
            .hide_outline = false,
            .hide_bottom = true,
            .num_ticks = 8,
            .start_angle = 135,
            .end_angle = 45,
            .angle_range = 270,
            .min_value = 0.0f,
            .max_value = 1.0f,
            .range_limits = {
                .min = rpm_data.range.min,
                .max = rpm_data.range.max,
            },
            .critical_zone = {
                .enabled = true,
                .start_percent = 0.8f,
                .color = THEME_COLOR_BLUE_1,
            }
        }
    };

    /* Cluster icons */
    static ClusterData::HandBrake hand_brake = ClusterData::HandBrake{

    };

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

    /* Draw gauges */
    DrawCircularGauge(&speedometer_data.gauge, this->delta_time);
    DrawCircularGauge(&rpm_data.gauge, this->delta_time);

    ImGui::PopFont();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

    /* Draw circular gauge editors */
    static bool show_speedometer_editor = true;
    DrawCircularGaugeEditor(speedometer_data.gauge, show_speedometer_editor, "Speedometer");

    static bool show_rpm_editor = true;
    DrawCircularGaugeEditor(rpm_data.gauge, show_rpm_editor, "RPM");

    ImGui::PopFont();

    // Create SVG Renderer for icon
    // ImGui::Image((void *)(intptr_t)texture, ImVec2(img_width, img_height), ImVec2(0, 1), ImVec2(1, 0));

    // ImGui::ShowDemoWindow();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glFlush();
}
