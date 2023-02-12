#include "velocimeter.hpp"

void Velocimeter::update(float dt)
{
  m_text.setCharacterSize(64);
  m_text.setString(std::to_string((int)this->value));
  m_text.setColor(sf::Color::Yellow);
}

void Velocimeter::setValue(float value)
{
  this->value = value;
  float angle = (value - min) / (max - min) * 180.f;
  m_needle.setRotation(angle);
}

void Velocimeter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_dial);
  target.draw(m_needle);
  target.draw(m_text);
}

Velocimeter::Velocimeter(const sf::Font &font, const sf::Vector2f &position,
                         const sf::Vector2f &size, float min, float max)
    : m_dial(), m_needle(), m_text(), min(min), max(max)
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

  m_text.setFont(font);
  m_text.setCharacterSize(30);
  m_text.setFillColor(sf::Color::White);
  m_text.setPosition(position.x + size.x / 2 - 30, position.y + size.y / 2 - 30);
}