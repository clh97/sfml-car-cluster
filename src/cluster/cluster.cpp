#include "cluster.hpp"
#include "velocimeter/velocimeter.hpp"

Cluster::Cluster()
{
  this->elapsed.restart();
}

Cluster::~Cluster()
{
}

float speedValue = 0.0f;
float rpmValue = 0.0f;
void Cluster::update()
{
  this->speedometer.update(0.0f);
  this->rpm.update(0.0f);

  if (this->elapsed.getElapsedTime().asSeconds() > 0.5f)
  {
    speedValue += 1.0f;
    rpmValue += 100.0f;
    this->speedometer.setValue(speedValue * 3.5f);
    this->rpm.setValue(rpmValue);
    this->elapsed.restart();
  }
}

void Cluster::draw(sf::RenderWindow &window)
{
  this->speedometer.draw(window, sf::RenderStates::Default);
  this->rpm.draw(window, sf::RenderStates::Default);
}