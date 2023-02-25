#include <iostream>
#include <cmath>
#include <random>
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "font.hpp"
#include "splash/splash.cpp"
#include "cluster/cluster.cpp"

using namespace std;

class Application
{
public:
    Application()
    {
        this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE);

        ImGui::SFML::Init(this->window);

        this->window.setFramerateLimit(APPLICATION_FPS);

        this->background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        this->background.setOrigin(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        this->background.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        this->background_shader.loadFromFile("shaders/circular_gradient.frag", sf::Shader::Fragment);
        this->background_shader.setUniform("center", sf::Glsl::Vec2(WINDOW_WIDTH / 2, 0.0f));
        this->background_shader.setUniform("radius", WINDOW_WIDTH / 1.0f);
        this->background_shader.setUniform("innerColor", sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        this->background_shader.setUniform("outerColor", sf::Glsl::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

        this->deltaClock.restart();
    }

    void run()
    {
        while (this->window.isOpen())
        {
            this->timeSinceLastUpdate += this->deltaClock.restart();

            sf::Event event;
            while (this->window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                    this->window.close();
            }

            while (this->timeSinceLastUpdate > this->timePerFrame)
            {
                this->timeSinceLastUpdate -= this->timePerFrame;
                ImGui::SFML::Update(this->window, this->timePerFrame);
                this->update(this->timePerFrame);
            }

            this->render(this->window);
            ImGui::SFML::Render(this->window);

            this->window.display();
        }

        ImGui::SFML::Shutdown();
    }

private:
    sf::RenderWindow window;
    sf::RectangleShape background;
    sf::Shader background_shader;
    sf::Clock deltaClock;
    const sf::Time timePerFrame = sf::seconds(1.0f / APPLICATION_FPS);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    Splash splash = Splash();
    Cluster cluster = Cluster();

    void render(sf::RenderWindow &window)
    {
        window.clear(sf::Color::Black);

        if (!this->splash.isDone())
        {
            this->splash.draw(window);
            return;
        }

        this->window.draw(this->background, &this->background_shader);
        this->cluster.draw(window);
    }

    void update(sf::Time elapsed)
    {
        this->window.setTitle(string(WINDOW_TITLE) + " | FPS: " + to_string(1.0f / elapsed.asSeconds()));
        if (!this->splash.isDone())
        {
            this->splash.update();
            return;
        }

        this->cluster.update(elapsed);
    };
};

int main()
{
    // cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

    Application app = Application();

    app.run();
}
