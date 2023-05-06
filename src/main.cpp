#include <memory>
#include <fmt/format.h>
#include <unistd.h>

#include "application.hpp"
#include "cluster_data.hpp"
#include "config.hpp"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fmt::print("SDL could not initialize! SDL_Error: {}\n", SDL_GetError());
        return 1;
    }

    std::unique_ptr<PlatformAdapter> adapter = std::make_unique<OpenGLAdapter>();

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

    auto calc_icon_pos = [](int index) -> ImVec2
    {
        // int x = (width / 2 - ((IC_ICON_DEFAULT_SIZE.x - IC_ICON_DEFAULT_HORIZONTAL_GAP) * IC_ICON_DEFAULT_ROW_QTY)) + (index % IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_HORIZONTAL_GAP + IC_ICON_DEFAULT_SIZE.x);
        int row_size = (IC_ICON_DEFAULT_SIZE.x + IC_ICON_DEFAULT_HORIZONTAL_GAP) * IC_ICON_DEFAULT_ROW_QTY;
        int x_offset = IC_ICON_DEFAULT_SIZE.x / 2 - IC_ICON_DEFAULT_HORIZONTAL_GAP / 2;
        int x = ((width / 2) - (row_size / 2)) + (index % IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_HORIZONTAL_GAP + IC_ICON_DEFAULT_SIZE.x) - x_offset;
        int y = (height - IC_ICON_DEFAULT_SIZE.y * 3) + (index / IC_ICON_DEFAULT_ROW_QTY) * (IC_ICON_DEFAULT_VERTICAL_GAP + IC_ICON_DEFAULT_SIZE.y);
        return ImVec2(x, y);
    };

    std::unique_ptr<Config> config = std::make_unique<Config>("../config.yaml");

    for (auto &gauge : config->GetClusterData().gauges)
    {
        fmt::print("{}", gauge->format.c_str());
    }

    // ClusterData _cluster_data = config->GetClusterData();
    // std::unique_ptr<ClusterData> cluster_data = std::make_unique<ClusterData>(_cluster_data.);

    // InstrumentClusterApplication app(std::move(adapter), std::move(cluster_data), title.c_str(), width, height);

    // app.Run();

    SDL_Quit();
    return 0;
}
