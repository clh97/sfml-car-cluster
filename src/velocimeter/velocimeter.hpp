#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class Velocimeter : public sf::Drawable
{
public:
  Velocimeter(const sf::Font &font, const sf::Vector2f &position,
              const sf::Vector2f &size, float min, float max);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void update(float dt);

  void setValue(float value);

private:
  sf::RectangleShape m_background;
  sf::Text m_text;
  sf::CircleShape m_dial;
  sf::RectangleShape m_needle;

  float min;
  float max;
  float value = 0.0f;
  const float dialRadius = 200.f;
  const float needleLength = dialRadius * 0.8f;
};