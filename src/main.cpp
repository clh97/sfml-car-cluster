#include <memory>
#include <fmt/format.h>

#include "application.hpp"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fmt::print("SDL could not initialize! SDL_Error: {}\n", SDL_GetError());
        return 1;
    }

    std::unique_ptr<PlatformAdapter> adapter = std::make_unique<OpenGLAdapter>();

    ImGuiApplication app(std::move(adapter), "SDL Instrument Cluster", 1920, 550);

    app.Run();

    SDL_Quit();
    return 0;
}
