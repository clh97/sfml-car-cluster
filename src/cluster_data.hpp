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

        struct
        {
            int min;
            int max;
        } range;

        CircularGauge gauge;
    } rpm;

    struct Fuel
    {
        float fuel = 0;
        std::string format = "{} L";
        struct
        {
            int min;
            int max;
        } range;

        CircularGauge gauge;
    } fuel;

    struct HandBrake
    {
        bool engaged = false;
        ClusterIcon icon;
    } hand_brake;

    struct Headlights
    {
        bool on = false;
        bool high_beam = false;
        ClusterIcon icon;
    } headlights;

    struct Wipers
    {
        bool on = false;
        ClusterIcon icon;
    } wipers;

    struct ArrowLeft
    {
        bool on = false;
        ClusterIcon icon;
    } arrow_left;

    struct ArrowRight
    {
        bool on = false;
        ClusterIcon icon;
    } arrow_right;

    // TODO - ClusterLabel entity handling: gear, time, etc.

    ClusterData() : rpm{}, speedometer{}, fuel{}, hand_brake{}, headlights{}, wipers{}  {}
};
