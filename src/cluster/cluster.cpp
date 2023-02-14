#include "cluster.hpp"
#include "velocimeter/velocimeter.hpp"

Cluster::Cluster()
{
  this->elapsed.restart();
}

Cluster::~Cluster()
{
}

void Cluster::update(sf::Time elapsed)
{
  this->speedometer.update(elapsed);
  this->rpm.update(elapsed);

  this->speed += 1 * 0.25f;
  this->rpmValue += 100 * 0.25f;

  if (this->speed > 200)
  {
    this->speed = 0;
  }

  if (this->rpmValue > 8000)
  {
    this->rpmValue = 0;
  }

  this->speedometer.setValue(this->speed);
  this->rpm.setValue(this->rpmValue);
  this->elapsed.restart();
}

void Cluster::draw(sf::RenderWindow &window)
{
  this->speedometer.draw(window, sf::RenderStates::Default);
  this->rpm.draw(window, sf::RenderStates::Default);
}