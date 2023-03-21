#pragma once
#include <cmath>

class Interpolation
{
public:
    template<typename T, typename U>
    static constexpr T linear(T const& x, T const& y, U const& a)
    {
        return static_cast<T>(x * (U(1) - a) + y * a);
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
