#pragma once
#include <SFML/Graphics.hpp>

#include "config.h"
#include "font.hpp"
#include "velocimeter/velocimeter.cpp"
#include "progress/progress.cpp"
#include "semi_meter/semi_meter.cpp"

class Cluster
{
public:
    Cluster();
    ~Cluster();

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow &window);

    float speedValue = 0;
    float rpmValue = 0;
    float fuelValue = 0;
    float oilValue = 0;
    float temperatureValue = 0;

private:
    Velocimeter speedometer = Velocimeter(
        OpenSans::GetInstance().GetFont(),
        sf::Vector2f(SPEEDOMETER_X, SPEEDOMETER_Y),
        sf::Vector2f(SPEEDOMETER_RADIUS, SPEEDOMETER_RADIUS),
        SPEEDOMETER_MIN_VALUE, SPEEDOMETER_MAX_VALUE, " km/h");
    Velocimeter rpm = Velocimeter(
        OpenSans::GetInstance().GetFont(),
        sf::Vector2f(RPM_X, RPM_Y),
        sf::Vector2f(RPM_RADIUS, RPM_RADIUS),
        RPM_MIN_VALUE, RPM_MAX_VALUE, " rpm");
    // Progress rpm = Progress(
    //     sf::Vector2f(RPM_X, RPM_Y),
    //     RPM_RADIUS,
    //     RPM_MIN_VALUE, RPM_MAX_VALUE);
    SemiMeter fuel = SemiMeter(
        sf::Vector2f(FUEL_X, FUEL_Y),
        sf::Vector2f(FUEL_WIDTH, FUEL_HEIGHT),
        FUEL_MIN_VALUE, FUEL_MAX_VALUE, " %");
    SemiMeter oil_pressure = SemiMeter(
        sf::Vector2f(OIL_X, OIL_Y),
        sf::Vector2f(OIL_WIDTH, OIL_HEIGHT),
        OIL_MIN_VALUE, OIL_MAX_VALUE, " PSI");
    SemiMeter temperature = SemiMeter(
        sf::Vector2f(TEMPERATURE_X, TEMPERATURE_Y),
        sf::Vector2f(TEMPERATURE_WIDTH, TEMPERATURE_HEIGHT),
        TEMPERATURE_MIN_VALUE, TEMPERATURE_MAX_VALUE, " °C");
    sf::Clock deltaTime;
};
