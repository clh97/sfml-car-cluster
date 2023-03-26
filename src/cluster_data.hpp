#pragma once
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/components/circular_gauge.cpp"
#include "imgui/components/cluster_icon.cpp"

class ClusterData
{
public:
    struct Speedometer
    {
        float kmh_speed = 0;

        std::string format = "{} km/h";
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

    struct HandBrake
    {
        bool engaged = false;
        ClusterIcon icon;
    } hand_brake;

    ClusterData() : rpm{}, speedometer{}, hand_brake{} {}
};
