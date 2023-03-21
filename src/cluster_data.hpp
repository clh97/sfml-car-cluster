#pragma once
#include <iostream>

#include "imgui/imgui.h"

#include "imgui/components/circular_gauge.cpp"

class ClusterData
{
public:
    struct Speedometer
    {
        // Represents the current speed of the car
        float kmh_speed = 0;

        // Format string to use when displaying the label
        std::string format = "{} km/h";

        // Represents the range of the gauge (in km/h)
        struct
        {
            int min;
            int max;
        } range;

        CircularGauge gauge;
    } speedometer;

    struct RPM
    {
        float rpm = 0;
        std::string format = "{} RPM";

        struct {
            int min;
            int max;
        } range;

        CircularGauge gauge;
    } rpm;

    ClusterData() : speedometer{} {}
};
