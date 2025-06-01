#include "data_processing.hpp"
#include <numeric>

float DataProcessing::Combined(const std::array<float,3>& a,
                               const std::array<float,3>& b)
{
    const float mA = std::accumulate(a.begin(), a.end(), 0.f) / 3;
    const float mB = std::accumulate(b.begin(), b.end(), 0.f) / 3;
    return (mA + mB) / 2;
}