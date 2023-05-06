#pragma once
#include <yaml-cpp/yaml.h>

#include "cluster_data.hpp"

class Config
{
public:
  Config(std::string path);
  ClusterData GetClusterData();

  template <typename T>
  T get_config_value(std::string key);

private:
  std::unique_ptr<YAML::Node> config;
  YAML::Node GetNode(std::string key);
};

namespace YAML
{

  template <>
  struct convert<ClusterData>
  {
    static bool decode(const Node &node, ClusterData &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      std::vector<ClusterIcon> lights = node["icons"].as<std::vector<ClusterIcon>>();
      std::vector<CircularGauge> gauges = node["gauges"].as<std::vector<CircularGauge>>();

      for (auto &icon : lights)
      {
        std::unique_ptr<ClusterLightIndicator> icon_data = std::make_unique<ClusterLightIndicator>();
        icon_data->icon = std::move(icon);
        rhs.lights.push_back(std::move(icon_data));
      }

      for (auto &gauge : gauges)
      {
        std::unique_ptr<CircularGaugeData<float>> gauge_data = std::make_unique<CircularGaugeData<float>>();
        gauge_data->gauge = std::move(gauge);
        rhs.gauges.push_back(std::move(gauge_data));
      }

      return true;
    }
  };

  template <>
  struct convert<CircularGauge::CriticalZone>
  {
    static bool decode(const Node &node, CircularGauge::CriticalZone &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      rhs.enabled = node["enabled"].as<bool>();
      rhs.start_percent = node["start_percentage"].as<float>();
      return true;
    }
  };

  template <>
  struct convert<CircularGauge>
  {
    static bool decode(const Node &node, CircularGauge &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      fmt::print("cgauge: {}\n", node["name"].as<std::string>());

      rhs.radius = node["radius"].as<int>();
      rhs.center = ImVec2(node["center"][0].as<float>(), node["center"][1].as<float>());
      rhs.hide_outline = node["hide_outline"].as<bool>();
      rhs.hide_bottom = node["hide_bottom"].as<bool>();
      rhs.num_ticks = node["num_ticks"].as<int>();
      rhs.start_angle = node["start_angle"].as<float>();
      rhs.angle_range = node["angle_range"].as<float>();
      rhs.end_angle = node["start_angle"].as<float>() + node["angle_range"].as<float>();
      rhs.critical_zone.enabled = node["critical_zone"]["enabled"].as<bool>();
      rhs.critical_zone.start_percent = node["critical_zone"]["start"].as<float>();

      return true;
    }
  };

  template <typename T>
  struct convert<CircularGaugeData<T>>
  {
    static bool decode(const Node &node, CircularGaugeData<T> &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      rhs.name = node["name"].as<std::string>();
      rhs.format = node["format"].as<std::string>();
      rhs.range.min = node["range"]["min"].as<T>();
      rhs.range.max = node["range"]["max"].as<T>();
      fmt::print("gauge: {}\n", rhs.gauge);
      rhs.gauge = node["gauge"].as<CircularGauge>();

      return true;
    }
  };

  template <>
  struct convert<ClusterLightIndicator>
  {
    static bool decode(const Node &node, ClusterLightIndicator &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      rhs.icon = node["icon"].as<ClusterIcon>();
      return true;
    }
  };

  template <>
  struct convert<ClusterIcon>
  {
    static bool decode(const Node &node, ClusterIcon &rhs)
    {
      if (!node.IsMap())
      {
        return false;
      }

      rhs.name = node["name"].as<std::string>();
      rhs.path = node["path"].as<std::string>();
      rhs.position_index = node["position_index"].as<int>();
      return true;
    }
  };
}
