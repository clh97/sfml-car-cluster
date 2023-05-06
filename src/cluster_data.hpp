#pragma once

#include <iostream>
#include <vector>
#include <fmt/format.h>

#include "constants.hpp"
#include "imgui/imgui.h"
#include "imgui/components/circular_gauge.cpp"
#include "imgui/components/cluster_icon.cpp"

struct ClusterData
{
    std::vector<std::unique_ptr<ClusterLightIndicator>> lights;
    std::vector<std::unique_ptr<CircularGaugeData<float>>> gauges;
};