#include "velocimeter.hpp"
#include "effects/interpolate.hpp"

void Velocimeter::update(float dt)
{
  m_text.setCharacterSize(32);
  m_text.setString(std::to_string((int)this->value));
  m_text.setColor(sf::Color::White);
  m_text.setPosition(m_dial.getPosition().x - m_text.getGlobalBounds().width / 2,
                     m_dial.getPosition().y + this->dialRadius * 0.5f);
}

void Velocimeter::setValue(float value)
{
  this->value = value;
  float angle = (value - min) / (max - min) * 180.f;
  float interpolatedAngle = Interpolate::linearInterpolate(m_needle.getRotation(), angle, 0.1f);
  m_needle.setRotation(interpolatedAngle);
}

void Velocimeter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_dial);
  target.draw(m_needle);
  target.draw(m_needle_center);
  target.draw(m_text);
}

Velocimeter::Velocimeter(const sf::Font &font, const sf::Vector2f &position,
                         const sf::Vector2f &size, float min, float max)
    : m_dial(), m_needle_center(), m_needle(), m_text(), min(min), max(max)
{
  m_dial.setRadius(this->dialRadius);
  m_dial.setFillColor(sf::Color::Black);
  m_dial.setOutlineColor(sf::Color::White);
  m_dial.setOutlineThickness(2.f);
  m_dial.setOrigin(this->dialRadius, this->dialRadius);
  m_dial.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_needle.setSize(sf::Vector2f(needleLength, 5.f));
  m_needle.setFillColor(sf::Color::Red);
  m_needle.setOrigin(needleLength, 0);
  m_needle.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_needle_center.setRadius(this->dialRadius * 0.1f);
  m_needle_center.setFillColor(sf::Color::White);
  m_needle_center.setOrigin(this->dialRadius * 0.1f, this->dialRadius * 0.1f);
  m_needle_center.setPosition(position.x + size.x / 2, position.y + size.y / 2);

  m_text.setFont(font);
  m_text.setFillColor(sf::Color::White);
  m_text.setPosition(position.x + size.x / 2 - m_text.getGlobalBounds().width, position.y + size.y / 2 + this->dialRadius * 0.5f);
}