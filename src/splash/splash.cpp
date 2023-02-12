#include "splash.hpp"
#include "config.h"
#include "effects/fade.hpp"

Splash::Splash()
{
  this->splashClock.restart();
  this->splashTexture.loadFromFile("assets/ford.png");
  this->splashSprite.setTexture(this->splashTexture);
  this->splashSprite.setPosition(WINDOW_WIDTH / 2 - this->splashTexture.getSize().x / 2, WINDOW_HEIGHT / 2 - this->splashTexture.getSize().y / 2);
  this->splashSprite.setColor(sf::Color(255, 255, 255, 0));
}

void Splash::draw(sf::RenderWindow &window)
{
  window.draw(this->splashSprite);
}

bool Splash::update()
{
  if (!this->splashEntryDone && !this->splashDone)
  {
    bool doneFading = Fade::fadeSprite(this->splashSprite, this->splashClock, sf::seconds(2), true);

    if (doneFading)
    {
      this->splashEntryDone = true;
    }
  }

  if (this->splashEntryDone && !this->splashDone)
  {
    bool doneFading = Fade::fadeSprite(this->splashSprite, this->splashClock, sf::seconds(1.15), false);
    if (doneFading)
    {
      this->splashDone = true;
    }
  }

  return this->splashDone && this->splashEntryDone;
}

bool Splash::isDone()
{
  return this->splashDone && this->splashEntryDone;
}