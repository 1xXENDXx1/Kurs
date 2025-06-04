#include "hr_generator.hpp"
#include "hr_sensor.hpp"

void HrGenerator::Init()
{
    RCC::AHB1ENR::GPIOAEN::Enable::Set();

    GPIOA::MODER ::MODER2::Alternate::Set();
    GPIOA::AFRL  ::AFRL2 ::Af1      ::Set();
    GPIOA::OSPEEDR::OSPEEDR2::HighSpeed::Set();

    RCC::APB1ENR::TIM2EN::Enable::Set();
    TIM2::PSC::Write(Prescaler);

    TIM2::CCMR2_Output::CC3S::Set(0);
    TIM2::CCMR2_Output::OC3M::Set(6);    // toggle
    TIM2::CCER::CC3E::Set(1);

    TIM2::CR1::CEN::Set(1);
}

void HrGenerator::SetFrequency(uint32_t Hz)
{
    const uint32_t Ftick = SystemCoreClock / (Prescaler + 1);
    const uint32_t arr   = 2*Ftick / Hz - 1;

    TIM2::ARR ::Write(arr);
    TIM2::CCR3::Write((arr + 1) / 2);
    TIM2::EGR ::Write(1U);               // update
    
    HrSensor::SetExpectedHz(static_cast<uint16_t>(Hz));
}

HrGenerator gHrGen;