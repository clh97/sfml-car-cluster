#include "splash.hpp"
#include "config.h"
#include "effects/fade.hpp"

Splash::Splash()
{
  this->splashClock.restart();
  this->splashTexture.loadFromFile(FORD_LOGO_PATH);
  this->splashSprite.setTexture(this->splashTexture);
  this->splashSprite.setPosition(WINDOW_WIDTH / 2 - this->splashTexture.getSize().x / 2, WINDOW_HEIGHT / 2 - this->splashTexture.getSize().y / 2);
  this->splashSprite.setColor(sf::Color(255, 255, 255, 0));
}

Splash::~Splash()
{
  this->splashTexture.~Texture();
  this->splashSprite.~Sprite();
  this->splashClock.~Clock();
}

void Splash::draw(sf::RenderWindow &window)
{
  window.draw(this->splashSprite);
}

bool Splash::update()
{
  if (!this->splashEntryDone && !this->splashDone)
  {
    bool doneFading = Fade::fadeSprite(this->splashSprite, this->splashClock, sf::seconds(SPLASH_FADEIN_TIME), true);

    if (doneFading)
    {
      this->splashEntryDone = true;
    }
  }

  if (this->splashEntryDone && !this->splashDone)
  {
    bool doneFading = Fade::fadeSprite(this->splashSprite, this->splashClock, sf::seconds(SPLASH_FADEOUT_TIME), false);
    if (doneFading)
    {
      this->splashDone = true;
    }
  }

  return this->splashDone && this->splashEntryDone;
}

bool Splash::isDone()
{
  if (SKIP_SPLASH)
  {
    return true;
  }

  return this->splashDone && this->splashEntryDone;
}