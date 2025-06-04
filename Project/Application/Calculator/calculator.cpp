#include "calculator.hpp"
#include <cmath>

float Calculator::RawToGlucose(uint16_t r)
{
    constexpr float Vref = 3.275f;
    float v = r * Vref / 4093.0f;
    float R = 10'000 * (3.3f / v - 1.0f);
    float tK = 1.0f / (1.0f / 298.15f + std::log(R / 10'000) / 3950);
    return 10.31f * (tK - 273.15f - 36.37f);
}

float Calculator::BpmToGlucose(int bpm)
{
    return 0.12f * (bpm - 75);
}