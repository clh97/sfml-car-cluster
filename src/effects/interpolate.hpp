#pragma once
#include <SFML/Graphics.hpp>

class Interpolate
{
public:
  static int linearInterpolate(float start, float end, float percent)
  {
    return start + (end - start) * percent;
  }

  static float sinusoidalInterpolate(float start, float end, float t)
  {
    float range = end - start;
    float value = range * (std::sin(t * PI) + 1.f) / 2.f + start;
    return value;
  }

  static float mapValue(float value, float inMin, float inMax, float outMin, float outMax)
  {
    float result = (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    return result;
  }

  static sf::Color rgbaInterpolate(sf::Color start, sf::Color end, float percent)
  {
    int r = linearInterpolate(start.r, end.r, percent);
    int g = linearInterpolate(start.g, end.g, percent);
    int b = linearInterpolate(start.b, end.b, percent);
    int a = linearInterpolate(start.a, end.a, percent);
    return sf::Color(r, g, b, a);
  }
};