#pragma once
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
  sf::Text m_text;
  sf::CircleShape m_dial;
  sf::RectangleShape m_needle;
  sf::CircleShape m_needle_center;
  sf::CircleShape m_background;
  sf::Shader m_circular_gradient_shader;
  std::vector<sf::RectangleShape>
      m_ticks;

  float min;
  float max;
  float value;
  float dialRadius;
  const float needleLength = dialRadius;
  std::string textSuffix;
};