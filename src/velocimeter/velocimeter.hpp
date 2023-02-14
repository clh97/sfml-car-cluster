#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Velocimeter : public sf::Drawable
{
public:
  Velocimeter(const sf::Font &font, const sf::Vector2f &position,
              const sf::Vector2f &size, float min, float max, std::string textSuffix = "");

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void update(sf::Time elapsed);

  void setValue(float value);

private:
  sf::RectangleShape m_background;
  sf::Text m_text;
  sf::CircleShape m_dial;
  sf::RectangleShape m_needle;
  sf::CircleShape m_needle_center;
  std::vector<sf::RectangleShape> m_ticks;

  float min;
  float max;
  float value;
  const float dialRadius = 200.f;
  const float needleLength = dialRadius * 0.95f;
  std::string textSuffix;
};