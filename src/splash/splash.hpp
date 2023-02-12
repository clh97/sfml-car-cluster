#pragma once
#include <SFML/Graphics.hpp>

class Splash
{
public:
  Splash();
  ~Splash();
  void draw(sf::RenderWindow &window);
  bool update();
  bool isDone();

private:
  bool splashDone = false;
  bool splashEntryDone = false;
  sf::Texture splashTexture;
  sf::Sprite splashSprite;
  sf::Clock splashClock;
};
