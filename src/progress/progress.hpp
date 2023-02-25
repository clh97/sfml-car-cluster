#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "config.h"
#include "effects/interpolate.hpp"

class Progress : public sf::Drawable
{
public:
    Progress(
        const sf::Vector2f &position,
        float radius,
        float min,
        float max,
        sf::Color background_color = sf::Color::White,
        sf::Color progress_color = sf::Color::Red);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void update(sf::Time elapsed);

    void setValue(float value);

private:
    sf::CircleShape m_background;
    sf::Vector2f m_position;
    sf::VertexArray m_vertexArray;

    float min;
    float max;
    float value;
    float radius;
};
