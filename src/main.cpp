#include <memory>

#include <fmt/format.h>

#include <unistd.h>

#include "application.hpp"

#include "cluster_data.hpp"

int main(int argc, char * argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fmt::print("SDL could not initialize! SDL_Error: {}\n", SDL_GetError());
        return 1;
    }

    std::unique_ptr <PlatformAdapter> adapter = std::make_unique < OpenGLAdapter > ();

    const int width = 1920;
    const int height = 550;
    const std::string title = "Cluster";

    /* Instrument cluster components */
    /* Speedometer gauge */

    /* Instrument cluster icons */
    #define IC_ICON_DEFAULT_SIZE ImVec2(64, 64)
    #define IC_ICON_DEFAULT_HORIZONTAL_GAP 32
    #define IC_ICON_DEFAULT_VERTICAL_GAP 16
    #define IC_ICON_DEFAULT_ROW_QTY 5

    auto calc_icon_pos = [](int index) -> ImVec2 {
        // int x = (width / 2 - ((IC_ICON_DEFAULT_SIZE.x - IC_ICON_DEFAULT_HORIZONTAL_GAP) * IC_ICON_DEFAULT_ROW_QTY)) + (index % IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_HORIZONTAL_GAP + IC_ICON_DEFAULT_SIZE.x);
        int row_size = (IC_ICON_DEFAULT_SIZE.x + IC_ICON_DEFAULT_HORIZONTAL_GAP) * IC_ICON_DEFAULT_ROW_QTY;
        int x_offset = IC_ICON_DEFAULT_SIZE.x / 2 - IC_ICON_DEFAULT_HORIZONTAL_GAP / 2;
        int x = ((width / 2) - (row_size / 2)) + (index % IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_HORIZONTAL_GAP + IC_ICON_DEFAULT_SIZE.x) - x_offset;
        int y = (height - IC_ICON_DEFAULT_SIZE.y * 3) + (index / IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_VERTICAL_GAP + IC_ICON_DEFAULT_SIZE.y);
        return ImVec2(x, y);
    };

    std::unique_ptr < ClusterData > cluster_data = std::make_unique < ClusterData > (ClusterData {
        .speedometer = ClusterData::GaugeData<int>{
                .value = 0,
                    .format = "%d km/h",
                    .range = {
                        0,
                        280
                    },
                    .gauge = {
                        .center = {
                            static_cast < float > ((width / 2.75 - 250) - 50),
                            static_cast < float > (height * 0.5),
                        },
                        .radius = 250,
                        .label = "",
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
            },
            .rpm = ClusterData::GaugeData<int>{
                .value = 0,
                .format = "%d RPM",
                .range = {
                    0,
                    8000
                },
                .gauge = {
                    .center = {
                        static_cast < float > (width - (width / 2.75 - 250) - 50),
                        static_cast < float > (height * 0.5),
                    },
                    .radius = 250,
                    .label = "",
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
            },
            .fuel = ClusterData::GaugeData<int>{
                .value = 0, .format = "{} L", .range = {
                        .min = 0,
                        .max = 50,
                    },
                    .gauge {
                        .center = {
                                static_cast < float > (width / 2 - 300),
                                static_cast < float > (height / 2 + 140),
                            },
                            .radius = 60,
                            .label = "",
                            .bg_color = THEME_COLOR_TRANSPARENT,
                            .fg_color = THEME_COLOR_WHITE,
                            .needle_color = THEME_COLOR_BLUE_1,
                            .text_color = THEME_COLOR_WHITE,
                            .hide_outline = false,
                            .hide_bottom = true,
                            .num_ticks = 6,
                            .start_angle = 135,
                            .end_angle = 45,
                            .angle_range = 270,
                            .min_value = 0.0f,
                            .max_value = 1.0f,
                            .range_limits = {
                                .min = 0,
                                .max = 50,
                            },
                            .critical_zone = {
                                .enabled = true,
                                .start_percent = 0.2f,
                                .color = THEME_COLOR_YELLOW,
                            }
                    }
            },
            .hand_brake = {
                .cli = {
                    .icon = {
                        .path = "assets/images/hand_brake.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(0),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .headlights = {
                .cli = {
                    .icon = {
                        .path = "assets/images/headlights.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(2),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .wipers = {
                .cli = {
                    .icon {
                        .path = "assets/images/wipers.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(3),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .arrow_left = {
                .cli = {
                    .icon {
                        .path = "assets/images/arrow_left.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(0),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .arrow_right = {
                .cli = {
                    .icon {
                        .path = "assets/images/arrow_right.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(4),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .oil = {
                .cli = {
                    .icon {
                        .path = "assets/images/oil.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(5),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .battery = {
                .cli = {
                    .icon {
                        .path = "assets/images/battery.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(6),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .temperature = {
                .cli = {
                    .icon {
                        .path = "assets/images/temperature.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(7),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .engine = {
                .cli = {
                    .icon {
                        .path = "assets/images/engine.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(8),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .door_lock = {
                .cli = {
                    .icon {
                        .path = "assets/images/door_lock.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(9),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            },
            .abs = {
                .cli = {
                    .icon {
                        .path = "assets/images/abs.svg",
                        .texture = NULL,
                        .size = IC_ICON_DEFAULT_SIZE,
                        .position = calc_icon_pos(10),
                        .color = THEME_COLOR_DARK_GRAY,
                    }
                }
            }
    });

    InstrumentClusterApplication app(std::move(adapter), std::move(cluster_data), title.c_str(), width, height);

    app.Run();

    SDL_Quit();
    return 0;
}
