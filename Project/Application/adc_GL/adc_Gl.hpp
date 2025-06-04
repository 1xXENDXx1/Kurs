#ifndef ADC_HPP
#define ADC_HPP

#include <cstdint>
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "adc1registers.hpp"

class Adc {
public:
    explicit Adc(uint8_t ch);
    void     Init();
    uint16_t Sample();

private:
    uint8_t mCh;
};

#endif