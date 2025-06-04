#ifndef HR_SENSOR_HPP
#define HR_SENSOR_HPP

#include <cstdint>
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "tim2registers.hpp"
#include "nvicregisters.hpp"
#include "system_config.hpp"

class HrSensor {
public:
    void     Init();
    uint16_t SampleFreq() const;

    static void IRQHandler();
    static HrSensor& instance();
    
    static void SetExpectedHz(uint16_t Hz); 

private:
    HrSensor() = default;
    inline static volatile uint16_t freqHz_{0};
    inline static volatile uint16_t expectedHz_{0};
};

extern "C" void TIM2_IRQHandler();

#endif