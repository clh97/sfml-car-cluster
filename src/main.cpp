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
    #define IC_ICON_DEFAULT_SIZE ImVec2(64, 64)
    #define IC_ICON_DEFAULT_SPACING 16
    #define IC_ICON_DEFAULT_ROW_QTY 5

    auto calc_icon_pos = [](int index) -> ImVec2 {
        int x = (width / 2 - ((IC_ICON_DEFAULT_SIZE.x - IC_ICON_DEFAULT_SPACING) * IC_ICON_DEFAULT_ROW_QTY)) + (index % IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_SPACING + IC_ICON_DEFAULT_SIZE.x);
        int y = 32 + (index / IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_SPACING + IC_ICON_DEFAULT_SIZE.y);
        return ImVec2(x, y);
    };

    // Left arrow
    cluster_data->arrow_left = ClusterData::ArrowLeft{
        .icon = ClusterIcon{
            .path = "../src/assets/images/arrow_left.svg",
            .position = calc_icon_pos(0),
            .size = IC_ICON_DEFAULT_SIZE,
            .color = THEME_COLOR_DARK_GRAY,
            .texture = NULL,
        },
        .on = false,
    };

    // Hand brake
    cluster_data->hand_brake = ClusterData::HandBrake{
        .icon = ClusterIcon{
            .path = "../src/assets/images/parking_brake.svg",
            .position = calc_icon_pos(1),
            .size = IC_ICON_DEFAULT_SIZE,
            .color = THEME_COLOR_DARK_GRAY,
            .texture = NULL,
        },
        .engaged = false,
    };


    // Headlights
    cluster_data->headlights = ClusterData::Headlights{
        .icon = ClusterIcon{
            .path = "../src/assets/images/headlights.svg",
            .position = calc_icon_pos(2),
            .size = IC_ICON_DEFAULT_SIZE,
            .color = THEME_COLOR_DARK_GRAY,
            .texture = NULL,
        },
        .on = false,
        .high_beam = false,
    };

    // Wipers
    cluster_data->wipers = ClusterData::Wipers{
        .icon = ClusterIcon{
            .path = "../src/assets/images/wipers.svg",
            .position = calc_icon_pos(3),
            .size = IC_ICON_DEFAULT_SIZE,
            .color = THEME_COLOR_DARK_GRAY,
            .texture = NULL,
        },
        .on = false,
    };

    // Right arrow
    cluster_data->arrow_right = ClusterData::ArrowRight{
        .icon = ClusterIcon{
            .path = "../src/assets/images/arrow_right.svg",
            .position = calc_icon_pos(4),
            .size = IC_ICON_DEFAULT_SIZE,
            .color = THEME_COLOR_DARK_GRAY,
            .texture = NULL,
        },
        .on = false,
    };

    InstrumentClusterApplication app(std::move(adapter), std::move(cluster_data), title.c_str(), width, height);

    app.Run();

    SDL_Quit();
    return 0;
}
