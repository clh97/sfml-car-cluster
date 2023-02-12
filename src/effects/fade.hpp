#pragma once
#include <SFML/Graphics.hpp>

class Fade
{
public:
  static bool fadeSprite(sf::Sprite &sprite, sf::Clock &clock, sf::Time duration, bool fadeIn)
  {
    static const float MAX_ALPHA = 255.f;

    sf::Color color = sprite.getColor();
    float alpha = color.a;
    float delta = MAX_ALPHA / duration.asSeconds() * clock.restart().asSeconds();

    if (fadeIn)
    {
      alpha += delta;
      if (alpha > MAX_ALPHA)
      {
        alpha = MAX_ALPHA;
        return true;
      }
    }
    else
    {
      alpha -= delta;
      if (alpha < 0.f)
      {
        alpha = 0.f;
        return true;
      }
      clock.restart();
    }

    color.a = static_cast<sf::Uint8>(alpha);
    sprite.setColor(color);

    return false;
  }
};
