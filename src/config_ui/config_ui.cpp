#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "config.h"
#include "cluster/cluster.hpp"
#include "effects/interpolate.hpp"

class ConfigUi
{
private:
    Cluster *cluster;
    float speed = 0.0f;
    float rpm = 0.0f;
    float fuelLevel = 0.0f;
    float temperature = 0.0f;
    float multiplicationFactor = 0.001f;
    bool engineCheck = false;
    bool oilPressure = false;
    bool seatbelt = false;
    bool auto_values = false;

public:
    ConfigUi(Cluster *cluster)
    {
        this->cluster = cluster;
    }

    void display()
    {
        // Speedometer
        ImGui::Text("Speedometer");
        ImGui::SliderFloat("Speed", &speed, SPEEDOMETER_MIN_VALUE, SPEEDOMETER_MAX_VALUE);

        // Tachometer
        ImGui::Text("Tachometer");
        ImGui::SliderFloat("RPM", &rpm, RPM_MIN_VALUE, RPM_MAX_VALUE);

        // Fuel gauge
        ImGui::Text("Fuel Gauge");
        ImGui::SliderFloat("Fuel Level", &fuelLevel, FUEL_MIN_VALUE, FUEL_MAX_VALUE);

        // Temperature gauge
        ImGui::Text("Temperature Gauge");
        ImGui::SliderFloat("Temperature", &temperature, TEMPERATURE_MIN_VALUE, TEMPERATURE_MAX_VALUE);

        ImGui::Separator();

        // Warning lights
        ImGui::Text("Warning Lights");
        ImGui::Checkbox("Engine Check", &engineCheck);
        ImGui::Checkbox("Oil Pressure", &oilPressure);
        ImGui::Checkbox("Seatbelt", &seatbelt);

        ImGui::Separator();

        // Automatic values
        ImGui::Text("Automatic values");
        ImGui::Checkbox("Automatic values", &auto_values);

        ImGui::Text("Multiplication factor");
        ImGui::SliderFloat("Multiplication factor", &multiplicationFactor, 0.0f, 1.0f);

        ImGui::Separator();

        ImGui::End();
    }

    void init()
    {
        ImGuiStyle *style = &ImGui::GetStyle();

        style->WindowPadding = ImVec2(15, 15);
        style->WindowPadding = ImVec2(15, 15);
        style->WindowRounding = 5.0f;
        style->FrameRounding = 12.0f;
        style->ItemSpacing = ImVec2(12, 8);
        style->ItemInnerSpacing = ImVec2(8, 6);
        style->IndentSpacing = 25.0f;
        style->ScrollbarSize = 15.0f;
        style->ScrollbarRounding = 9.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 3.0f;

        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.25f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style->Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    }

    void update(sf::Time deltaTime)
    {
        if (auto_values && !ImGui::IsAnyItemActive())
        {
            float speedRange = SPEEDOMETER_MAX_VALUE - SPEEDOMETER_MIN_VALUE;
            float rpmRange = RPM_MAX_VALUE - RPM_MIN_VALUE;
            float fuelLevelRange = FUEL_MAX_VALUE - FUEL_MIN_VALUE;
            float temperatureRange = TEMPERATURE_MAX_VALUE - TEMPERATURE_MIN_VALUE;

            float speedOffset = (speedRange / 2.0f) + SPEEDOMETER_MIN_VALUE;
            float rpmOffset = (rpmRange / 2.0f) + RPM_MIN_VALUE;
            float fuelLevelOffset = (fuelLevelRange / 2.0f) + FUEL_MIN_VALUE;
            float temperatureOffset = (temperatureRange / 2.0f) + TEMPERATURE_MIN_VALUE;

            float dividedMultiplicationFactor = multiplicationFactor / 100.0f;

            float speedMultiplier = VALUE_LIMIT_MULTIPLICATION_FACTOR(SPEEDOMETER_MIN_VALUE, SPEEDOMETER_MAX_VALUE) * dividedMultiplicationFactor;
            float rpmMultiplier = VALUE_LIMIT_MULTIPLICATION_FACTOR(RPM_MIN_VALUE, RPM_MAX_VALUE) * dividedMultiplicationFactor;
            float fuelLevelMultiplier = VALUE_LIMIT_MULTIPLICATION_FACTOR(FUEL_MIN_VALUE, FUEL_MAX_VALUE) * dividedMultiplicationFactor;
            float temperatureMultiplier = VALUE_LIMIT_MULTIPLICATION_FACTOR(TEMPERATURE_MIN_VALUE, TEMPERATURE_MAX_VALUE) * dividedMultiplicationFactor;

            static float speedPhase = 0.0f;
            static float rpmPhase = 0.0f;
            static float fuelLevelPhase = 0.0f;
            static float temperaturePhase = 0.0f;

            speedPhase += speedMultiplier * deltaTime.asSeconds();
            rpmPhase += rpmMultiplier * deltaTime.asSeconds();
            fuelLevelPhase += fuelLevelMultiplier * deltaTime.asSeconds();
            temperaturePhase += temperatureMultiplier * deltaTime.asSeconds();

            float speedPercent = Interpolate::mapValue(std::sin(speedPhase), -1.0f, 1.0f, 0.0f, 1.0f);
            float rpmPercent = Interpolate::mapValue(std::sin(rpmPhase), -1.0f, 1.0f, 0.0f, 1.0f);
            float fuelLevelPercent = Interpolate::mapValue(std::sin(fuelLevelPhase), -1.0f, 1.0f, 0.0f, 1.0f);
            float temperaturePercent = Interpolate::mapValue(std::sin(temperaturePhase), -1.0f, 1.0f, 0.0f, 1.0f);

            speed = Interpolate::linearInterpolate(SPEEDOMETER_MIN_VALUE, SPEEDOMETER_MAX_VALUE, speedPercent);
            rpm = Interpolate::sinusoidalInterpolate(RPM_MIN_VALUE, RPM_MAX_VALUE, rpmPercent);
            fuelLevel = Interpolate::sinusoidalInterpolate(FUEL_MIN_VALUE, FUEL_MAX_VALUE, fuelLevelPercent);
            temperature = Interpolate::sinusoidalInterpolate(TEMPERATURE_MIN_VALUE, TEMPERATURE_MAX_VALUE, temperaturePercent);
        }

        this->cluster->fuelValue = fuelLevel;
        this->cluster->rpmValue = rpm;
        this->cluster->speedValue = speed;
        this->cluster->temperatureValue = temperature;
    }
};
