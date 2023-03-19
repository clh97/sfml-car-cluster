#pragma once
#include <cmath>

class Interpolation
{
public:
    static float linear(float time, float start_value, float change, float duration)
    {
        return change * time / duration + start_value;
    }

    static float map_range(float value, float input_min, float input_max, float output_min, float output_max)
    {
        return output_min + (output_max - output_min) * ((value - input_min) / (input_max - input_min));
    }

    static float sinoidal(float t, float b, float c, float d)
    {
        return -c / 2 * (cosf(M_PI * t / d) - 1) + b;
    }

    static float exponential(float t, float b, float c, float d)
    {
        return c * powf(2, 10 * (t / d - 1)) + b;
    }
};
