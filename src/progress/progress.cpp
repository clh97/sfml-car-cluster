#include "progress.hpp"

Progress::Progress(
    const sf::Vector2f &position,
    float radius,
    float min,
    float max,
    sf::Color background_color,
    sf::Color progress_color)
    : min(min), max(max), value(0), radius(radius), m_position(position)
{
  m_background.setRadius(radius);
  m_background.setOrigin(m_background.getRadius(), m_background.getRadius());
  m_background.setPosition(position);
  m_background.setFillColor(background_color);
  m_background.setOutlineColor(sf::Color(0, 0, 0, 50));
  m_background.setOutlineThickness(2.f);
}

void Progress::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_background);
  target.draw(&m_vertexArray[0], m_vertexArray.getVertexCount(), sf::TrianglesFan);
}

void Progress::update(sf::Time elapsed)
{
  float progress = this->value / (max - min) * -1.0f;
  float angle = progress * 245.0f;

  int numPoints = 32;

  this->m_vertexArray = sf::VertexArray(sf::TriangleFan, numPoints + 2);
  m_vertexArray[0].position = sf::Vector2f(this->m_position.x, this->m_position.y);
  m_vertexArray[0].color = sf::Color::Red;
  for (int i = 0; i <= numPoints; i++)
  {
    float angleRadians = 45.0f - (angle / numPoints * i - 90.f) * PI / 180.f;
    m_vertexArray[i + 1].position = sf::Vector2f(
        this->m_position.x + cos(angleRadians) * this->radius,
        this->m_position.y + sin(angleRadians) * this->radius);

    sf::Color color;
    if (this->value / (max - min) > 0.8f)
    {
      color = sf::Color::Red;
    }
    else
    {
      color = sf::Color::Green;
    }

    m_vertexArray[i + 1].color = Interpolate::rgbaInterpolate(
        sf::Color::Green,
        sf::Color::Red,
        std::clamp(abs(progress) * 1.2f, 0.0f, 1.0f));
  }
}

void Progress::setValue(float value)
{
  this->value = value;
}