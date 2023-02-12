#include <iostream>
#include <cmath>
#include <random>

#include "splash/splash.cpp"
// #include "velocimeter/velocimeter.cpp"

using namespace std;

class Application
{
public:
    Application()
    {
        this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE);
        this->deltaClock.restart();
        this->elapsed.restart();
    }

    void run()
    {
        while (this->window.isOpen())
        {
            this->timeSinceLastUpdate += this->deltaClock.restart();

            sf::Event Event;
            while (this->window.pollEvent(Event))
            {
                if (Event.type == sf::Event::Closed)
                    this->window.close();
            }

            sf::Time elapsed = this->deltaClock.getElapsedTime();

            while (this->timeSinceLastUpdate > this->timePerFrame)
            {
                this->timeSinceLastUpdate -= this->timePerFrame;
                this->update(this->timePerFrame);
            }

            this->render(this->window);
            this->window.display();
        }
    }

private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
    sf::Clock elapsed;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::VertexArray vertices = sf::VertexArray(sf::Points, 1000);
    Splash splash = Splash();

    void render(sf::RenderWindow &window)
    {
        window.clear(sf::Color::Black);
        // window.draw(this->vertices);

        this->splash.draw(window);
    }

    void update(sf::Time elapsed)
    {
        this->window.setTitle(string(WINDOW_TITLE) + " | FPS: " + to_string(1.0f / elapsed.asSeconds()));
        if (!this->splash.isDone())
        {
            this->splash.update();
        }
    };
};

int main()
{
    // cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

    Application app = Application();

    app.run();
}