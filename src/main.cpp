#include <iostream>
#include <memory>

#include "application.hpp"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::unique_ptr<PlatformAdapter> adapter = std::make_unique<OpenGLAdapter>();

    ImGuiApplication app(std::move(adapter), "SDL Instrument Cluster", 1920, 550);

    app.Run();

    SDL_Quit();
    return 0;
}
