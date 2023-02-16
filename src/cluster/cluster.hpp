#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include "velocimeter/velocimeter.cpp"

class Cluster
{
public:
  Cluster();
  ~Cluster();

  void update(sf::Time elapsed);
  void draw(sf::RenderWindow &window);

private:
  // Velocimeter speedometer = Velocimeter(
  // OpenSans::GetInstance().GetFont(),
  // sf::Vector2f(VELOCIMETER_X, VELOCIMETER_Y),
  // sf::Vector2f(VELOCIMETER_WIDTH, VELOCIMETER_HEIGHT),
  // 0, 200, " km/h");
  Velocimeter rpm = Velocimeter(
      OpenSans::GetInstance().GetFont(),
      sf::Vector2f(RPM_X, RPM_Y),
      sf::Vector2f(RPM_WIDTH, RPM_HEIGHT),
      0, 8000, " rpm");
  float speed = 0;
  float rpmValue = 0;
  sf::Clock elapsed;
};