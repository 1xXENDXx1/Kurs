#ifndef HR_GENERATOR_HPP
#define HR_GENERATOR_HPP

#include <cstdint>
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "tim2registers.hpp"
#include "system_config.hpp"

class HrGenerator {
public:
    static constexpr uint16_t Prescaler = 15;  

    void Init();
    void SetFrequency(uint32_t Hz);
};

extern HrGenerator gHrGen;    

#endif