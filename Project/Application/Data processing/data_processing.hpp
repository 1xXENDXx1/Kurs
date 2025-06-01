#ifndef DATA_PROCESSING_HPP
#define DATA_PROCESSING_HPP

#include <array>

class DataProcessing {
public:
    static float Combined(const std::array<float,3>& a,
                          const std::array<float,3>& b);
};

#endif