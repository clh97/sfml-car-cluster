#pragma once
#include <iostream>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/components/circular_gauge.cpp"
#include "imgui/components/cluster_icon.cpp"

class ClusterLightIndicator {
public:
    bool on = false;
    ClusterIcon icon;
    ImVec4 color_on = THEME_COLOR_LIGHT_GRAY;
    ImVec4 color_off = THEME_COLOR_YELLOW;

    ClusterLightIndicator(ClusterIcon _icon) {
        icon = _icon;
    }
};

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
        ClusterLightIndicator cli;
    } hand_brake;

    struct Headlights
    {
        ClusterLightIndicator cli;
        bool high_beam = false;
    } headlights;

    struct Wipers
    {
        ClusterLightIndicator cli;
    } wipers;

    struct ArrowLeft
    {
        ClusterLightIndicator cli;
    } arrow_left;

    struct ArrowRight
    {
        ClusterLightIndicator cli;
    } arrow_right;

    struct Oil
    {
        ClusterLightIndicator cli;
    } oil;

    struct Battery
    {
        ClusterLightIndicator cli;
    } battery;

    struct Temperature
    {
        ClusterLightIndicator cli;
    } temperature;

    struct Engine
    {
        ClusterLightIndicator cli;
    } engine;

    struct DoorLock
    {
        ClusterLightIndicator cli;
    } door_lock;

    struct ABS
    {
        ClusterLightIndicator cli;
    } abs;

    std::vector<ClusterLightIndicator*> lights;

};
