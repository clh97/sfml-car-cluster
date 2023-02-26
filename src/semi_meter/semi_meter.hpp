#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class SemiMeter : public sf::Drawable
{
public:
  SemiMeter(const sf::Vector2f &position,
            const sf::Vector2f &size, float min, float max, std::string textSuffix = "");

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void update(sf::Time deltaTime);

  void setValue(float value);

private:
  sf::Text m_text;
  sf::VertexArray m_dial;
  sf::RectangleShape m_needle;
  sf::CircleShape m_needle_center;
  sf::Vector2f position;
  sf::Vector2f size;
  std::vector<sf::RectangleShape>
      m_ticks;

  float min;
  float max;
  float value;
  float dialRadius;
  const float needleLength = dialRadius * 0.8f;
  std::string textSuffix;
};
