#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <cstdint>

class Calculator {
public:
    static float RawToGlucose(uint16_t r);
    static float BpmToGlucose(int bpm);
};

#endif