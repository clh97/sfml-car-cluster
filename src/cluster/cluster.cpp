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
  this->speed += 1 * 0.25f;
  this->rpmValue += 100 * 0.25f;
  this->fuelValue += 0.1f;
  this->oilValue += 0.1f;

  if (this->speed > 200)
  {
    this->speed = 0;
  }

  if (this->rpmValue > 8000)
  {
    this->rpmValue = 0;
  }

  if (this->fuelValue > 100)
  {
    this->fuelValue = 0;
  }

  if (this->oilValue > 65)
  {
    this->oilValue = 0;
  }

  this->speedometer.setValue(this->speed);
  this->rpm.setValue(this->rpmValue);
  this->fuel.setValue(this->fuelValue);
  this->oil_pressure.setValue(this->oilValue);

  this->speedometer.update(elapsed);
  this->rpm.update(elapsed);
  this->fuel.update(elapsed);
  this->oil_pressure.update(elapsed);

  this->elapsed.restart();
}

void Cluster::draw(sf::RenderWindow &window)
{
  this->rpm.draw(window, sf::RenderStates::Default);
  this->speedometer.draw(window, sf::RenderStates::Default);
  this->fuel.draw(window, sf::RenderStates::Default);
  this->oil_pressure.draw(window, sf::RenderStates::Default);
}