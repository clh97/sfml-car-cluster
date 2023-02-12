#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class Velocimeter : public sf::Drawable
{
public:
  Velocimeter(const sf::Font &font, const sf::Vector2f &position,
              const sf::Vector2f &size, const sf::Color &color);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void update(float dt);

  void setValue(float value);

private:
  sf::RectangleShape m_background;
  sf::RectangleShape m_value;
  sf::Text m_text;
};

void Velocimeter::update(float dt)
{
  m_text.setString(std::to_string((int)std::round(m_value.getSize().x / m_background.getSize().x * 100)) + "%");
}

void Velocimeter::setValue(float value)
{
  m_value.setSize(sf::Vector2f(m_background.getSize().x * value, m_background.getSize().y));
}

void Velocimeter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_background);
  target.draw(m_value);
  target.draw(m_text);
}

Velocimeter::Velocimeter(const sf::Font &font, const sf::Vector2f &position,
                         const sf::Vector2f &size, const sf::Color &color)
    : m_background(size), m_value(size), m_text()
{
  m_background.setPosition(position);
  m_background.setFillColor(sf::Color::Black);
  m_background.setOutlineColor(sf::Color::White);
  m_background.setOutlineThickness(2);

  m_value.setPosition(position);
  m_value.setFillColor(color);

  m_text.setFont(font);
  m_text.setCharacterSize(30);
  m_text.setFillColor(sf::Color::White);
  m_text.setPosition(position.x + size.x / 2 - 10, position.y + size.y / 2 - 15);
}