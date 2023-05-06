#pragma once

#include "config.hpp"

Config::Config(std::string path)
{
  try
  {
    config = std::make_unique<YAML::Node>(YAML::LoadFile(path));
  }
  catch (const YAML::BadFile &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

YAML::Node Config::GetNode(std::string key)
{
  return config->operator[](key);
}

template <typename T>
T Config::get_config_value(std::string key)
{
  return GetNode(key).as<T>();
}

ClusterData Config::GetClusterData()
{
  std::vector<std::unique_ptr<CircularGauge>> gauges;
  std::vector<std::unique_ptr<ClusterIcon>> icons;

  ClusterData cluster_data = get_config_value<ClusterData>("cluster_data");

  fmt::print("cluster_data: {}\n", cluster_data.gauges.size());

  // for (const CircularGaugeData<float> gauge : gauge_data["gauges"].as<std::vector<CircularGaugeData<float>>>())
  // {
  //   fmt::print("gauge: {}\n", gauge.format);
  //   // gauges.push_back(std::make_unique<CircularGauge>(gauge));
  // }

  // for (const auto &light : GetNode("cluster_data.lights"))
  // {
  //   lights.push_back(std::make_unique<ClusterIcon>(light));
  // }

  return cluster_data;
}