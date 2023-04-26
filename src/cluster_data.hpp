#pragma once

#include <iostream>
#include <vector>
#include <fmt/format.h>

#include "constants.hpp"
#include "imgui/imgui.h"
#include "imgui/components/circular_gauge.cpp"
#include "imgui/components/cluster_icon.cpp"

class ClusterData
{
public:
    struct Range
    {
        int min;
        int max;
    };

    template <typename ValueType>
    struct GaugeData
    {
        ValueType value = 0;
        std::string format;
        Range range;
        CircularGauge gauge;
    };

    GaugeData<int> speedometer{0, "{} km/h"};
    GaugeData<int> rpm{0, "{} RPM"};
    GaugeData<int> fuel{0, "{} L"};

#define CLUSTER_LIGHT_INDICATOR_STRUCT(name) \
    struct name                              \
    {                                        \
        ClusterLightIndicator cli;           \
        bool on = false;                     \
        bool secondary = false;              \
    } name

    CLUSTER_LIGHT_INDICATOR_STRUCT(hand_brake);
    CLUSTER_LIGHT_INDICATOR_STRUCT(headlights);
    CLUSTER_LIGHT_INDICATOR_STRUCT(wipers);
    CLUSTER_LIGHT_INDICATOR_STRUCT(arrow_left);
    CLUSTER_LIGHT_INDICATOR_STRUCT(arrow_right);
    CLUSTER_LIGHT_INDICATOR_STRUCT(oil);
    CLUSTER_LIGHT_INDICATOR_STRUCT(battery);
    CLUSTER_LIGHT_INDICATOR_STRUCT(temperature);
    CLUSTER_LIGHT_INDICATOR_STRUCT(engine);
    CLUSTER_LIGHT_INDICATOR_STRUCT(door_lock);
    CLUSTER_LIGHT_INDICATOR_STRUCT(abs);

#undef CLUSTER_LIGHT_INDICATOR_STRUCT

    std::vector<ClusterLightIndicator *> lights;
};
