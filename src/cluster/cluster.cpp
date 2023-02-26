#include "cluster.hpp"
#include "velocimeter/velocimeter.hpp"

Cluster::Cluster()
{
    this->deltaTime.restart();
}

Cluster::~Cluster()
{
}

void Cluster::update(sf::Time deltaTime)
{
    this->speedometer.setValue(this->speedValue);
    this->rpm.setValue(this->rpmValue);
    this->fuel.setValue(this->fuelValue);
    this->oil_pressure.setValue(this->oilValue);
    this->temperature.setValue(this->temperatureValue);

    this->speedometer.update(deltaTime);
    this->rpm.update(deltaTime);
    this->fuel.update(deltaTime);
    this->oil_pressure.update(deltaTime);
    this->temperature.update(deltaTime);

    this->deltaTime.restart();
}

void Cluster::draw(sf::RenderWindow &window)
{
    this->speedometer.draw(window, sf::RenderStates::Default);
    this->rpm.draw(window, sf::RenderStates::Default);
    // this->fuel.draw(window, sf::RenderStates::Default);
    // this->oil_pressure.draw(window, sf::RenderStates::Default);
    // this->temperature.draw(window, sf::RenderStates::Default);
}
