#include <memory>
#include <fmt/format.h>
#include <unistd.h>

#include "application.hpp"
#include "cluster_data.hpp"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fmt::print("SDL could not initialize! SDL_Error: {}\n", SDL_GetError());
        return 1;
    }

    std::unique_ptr<PlatformAdapter> adapter = std::make_unique<OpenGLAdapter>();
    std::unique_ptr<ClusterData> cluster_data = std::make_unique<ClusterData>();

    const int width = 1920;
    const int height = 550;
    const std::string title = "Cluster";

    /* Instrument cluster components */
    /* Speedometer gauge */
    cluster_data->speedometer = ClusterData::Speedometer{
        .range = {0, 280},
        .format = "{} km/h",
        .kmh_speed = 0.0f,
        .gauge = {
            .label = "",
            .center = {
                static_cast<float>((width  / 2.75 - 250) - 50),
                static_cast<float>(height * 0.5),
            },
            .radius = 250,
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
                .min = 0,
                .max = 280,
            },
            .critical_zone = {
                .enabled = true,
                .start_percent = 0.75f,
                .color = THEME_COLOR_BLUE_1,
            }
        }
    };

    /* RPM gauge */
    cluster_data->rpm = ClusterData::RPM{
        .range = {0, 8000},
        .format = "{} RPM",
        .rpm = 0.0f,
        .gauge = {
            .label = "",
            .center = {
                static_cast<float>(width - (width / 2.75 - 250) - 50),
                static_cast<float>(height * 0.5),
            },
            .radius = 250,
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
                .min = 0,
                .max = 8000,
            },
            .critical_zone = {
                .enabled = true,
                .start_percent = 0.8f,
                .color = THEME_COLOR_BLUE_1,
            }
        }
    };

    /* Instrument cluster icons */
    cluster_data->hand_brake = ClusterData::HandBrake{
        .icon = ClusterIcon{
            .path = "../src/assets/images/parking_brake.svg",
            .position = ImVec2(1000, 275),
            .size = ImVec2(64, 64),
            .color = THEME_COLOR_LIGHT_GRAY,
            .texture = NULL,
        },
        .engaged = false,
    };

    ImGuiApplication app(std::move(adapter), std::move(cluster_data), title.c_str(), width, height);

    app.Run();

    SDL_Quit();
    return 0;
}
