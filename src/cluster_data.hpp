#pragma once
#include <iostream>
#include "imgui/imgui.h"

class ClusterData
{
public:
    struct Speedometer
    {
        // Represents the current speed of the car
        int kmh_speed = 0;

        // Format string to use when displaying the label
        std::string format = "{} km/h";

        // User-friendly label to display on the gauge
        std::string label = "0 km/h";

        // Initial angle of the needle
        float initial_angle = 0.0f;

        // Final angle of the needle
        float final_angle = 0.0f;

        // Represents the range of the gauge (in km/h)
        struct
        {
            int min;
            int max;
        } range;

        // Visual aspects of the gauge
        struct
        {
            float value = 0.0f;
            int radius = 150;
            ImVec2 pos = ImVec2(0, 0);
            ImColor needle_color = ImColor(255, 0, 0, 255);
            ImColor bg_color = ImColor(0, 0, 0, 128);
            ImColor fg_color = ImColor(0, 255, 0, 255);
            ImColor text_color = ImColor(255, 255, 255, 255);
            ImColor ticks_color = ImColor(255, 255, 255, 255);
        } gauge;
    } speedometer;

    ClusterData() : speedometer{} {}
};
