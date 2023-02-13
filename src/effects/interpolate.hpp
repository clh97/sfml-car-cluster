#pragma once
#include <SFML/Graphics.hpp>

class Interpolate
{
public:
  static int linearInterpolate(float start, float end, float percent)
  {
    return start + (end - start) * percent;
  }
};