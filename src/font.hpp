#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"

class OpenSans
{
public:
  static OpenSans &GetInstance()
  {
    static OpenSans instance;
    return instance;
  }

  sf::Font &GetFont() { return font_; }

private:
  OpenSans()
  {
    if (font_.loadFromFile(FONT_PATH))
    {
      std::cout << "Font loaded successfully" << std::endl;
    }
    else
    {
      std::cout << "Font failed to load" << std::endl;
    }
  }

  sf::Font font_;
};
