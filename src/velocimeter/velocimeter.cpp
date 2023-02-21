#include "velocimeter.hpp"
#include "effects/interpolate.hpp"

void Velocimeter::update(sf::Time elapsed)
{
  m_text.setCharacterSize(50);
  m_text.setString(std::to_string((int)this->value) + textSuffix);
  m_text.setColor(sf::Color::White);
  m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f);

  m_ticks.clear();
  m_ticks.reserve((int)max - (int)min);

  int iteration = 0;
  for (int i = (int)min; i <= max; i += max >= 1000 ? 1000 : 10)
  {
    float value = (float)i;
    float angle = 90.0f - (value - min) / (max - min) * 225.f;
    bool odd = iteration % 2;
    float tickLength = odd ? this->dialRadius * 0.1f : this->dialRadius * 0.05f;
    float tickWidth = odd ? 2.5f : 1.f;
    sf::Color tickColor = odd ? sf::Color::Red : sf::Color::White;

    sf::RectangleShape line(sf::Vector2f(2.f, tickLength));
    line.setOrigin(1.f, this->dialRadius * 0.9f);
    line.setFillColor(tickColor);
    line.setOutlineColor(tickColor);
    line.setOutlineThickness(tickWidth);
    line.setRotation(angle);
    line.setPosition(m_dial.getPosition().x, m_dial.getPosition().y);

    m_ticks.push_back(line);
    iteration++;
  }
}

void Velocimeter::setValue(float value)
{
  this->value = value;
  int angle = (value - min) / (max - min) * 225.f - 45.f;
  int rotation = m_needle.getRotation();
  float interpolateRotation = rotation;

  if (rotation < -45.f)
  {
    interpolateRotation = 360.f + rotation;
  }
  else if (rotation > 225.f)
  {
    interpolateRotation = rotation - 360.f;
  }

  float interpolatedAngle = Interpolate::sinusoidalInterpolate(interpolateRotation, angle, 0.1f);
  m_needle.setRotation(interpolatedAngle);

  if (value > this->max * 0.8f)
  {
    m_needle.setFillColor(sf::Color::Red);
  }
  else
  {
    m_needle.setFillColor(sf::Color::Green);
  }
}

void Velocimeter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_dial);
  target.draw(m_background, &m_circular_gradient_shader);
  for (const auto &tick : m_ticks)
  {
    target.draw(tick);
  }
  target.draw(m_needle);
  target.draw(m_needle_center);
  target.draw(m_text);
}

Velocimeter::Velocimeter(const sf::Font &font, const sf::Vector2f &position,
                         const sf::Vector2f &size, float min, float max, std::string textSuffix)
    : m_dial(), m_needle_center(), m_needle(), m_text(), min(min), max(max), dialRadius(size.x), textSuffix(textSuffix), m_background()
{
  value = min;

  m_dial.setRadius(this->dialRadius);
  m_dial.setFillColor(sf::Color::Black);
  m_dial.setOutlineColor(sf::Color(255, 255, 255, 50));
  m_dial.setOutlineThickness(2.f);
  m_dial.setOrigin(this->dialRadius, this->dialRadius);
  m_dial.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_needle.setSize(sf::Vector2f(needleLength, 6.f));
  m_needle.setFillColor(sf::Color::Red);
  m_needle.setOrigin(needleLength, 0.0f);
  m_needle.setPosition(position.x + size.x / 2, position.y + size.y / 2);
  m_needle.setRotation(45.f);

  m_needle_center.setRadius(this->dialRadius * 0.7f);
  m_needle_center.setFillColor(sf::Color::Black);
  // m_needle_center.setOutlineColor(sf::Color::White);
  // m_needle_center.setOutlineThickness(2.f);
  m_needle_center.setOrigin(this->dialRadius * 0.7f, this->dialRadius * 0.7f);
  m_needle_center.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_text.setFont(font);
  m_text.setFillColor(sf::Color::White);
  m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f);
  m_text.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_circular_gradient_shader.loadFromFile("shaders/circular_gradient.frag", sf::Shader::Fragment);
  m_circular_gradient_shader.setUniform("center", sf::Glsl::Vec2(position.x + size.x / 2, position.y + size.y / 2));
  m_circular_gradient_shader.setUniform("radius", this->dialRadius);
  m_circular_gradient_shader.setUniform("innerColor", sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
  m_circular_gradient_shader.setUniform("outerColor", sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 0.2f));

  m_background.setRadius(this->dialRadius);
  m_background.setOrigin(this->dialRadius, this->dialRadius);
  m_background.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  this->update(sf::Time::Zero);
}