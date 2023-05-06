#pragma once

#include <memory>

#include "cluster_data.hpp"

// ClusterData::ClusterData(std::vector<ClusterIcon> &_icons,
//                          std::vector<CircularGauge> &_gauges)
// {
//   for (auto &icon : _icons)
//   {
//     std::unique_ptr<ClusterLightIndicator> icon_data = std::make_unique<ClusterLightIndicator>();
//     icon_data->icon = std::move(icon);
//     this->lights.push_back(std::move(icon_data));
//   }

//   for (auto &gauge : _gauges)
//   {
//     std::unique_ptr<CircularGaugeData<float>> gauge_data = std::make_unique<CircularGaugeData<float>>();
//     gauge_data->gauge = std::move(gauge);
//     this->gauges.push_back(std::move(gauge_data));
//   }
// }