#include "hr_sensor.hpp"
#include "hr_generator.hpp"




HrSensor& HrSensor::instance()
{
    static HrSensor s;
    return s;
}

void HrSensor::Init()
{
    RCC::AHB1ENR::GPIOAEN::Enable::Set();

    GPIOA::MODER ::MODER1::Alternate::Set();
    GPIOA::AFRL  ::AFRL1 ::Af1      ::Set();

    TIM2::CCMR1_Input::CC2S::Set(1);
    TIM2::CCER::CC2P::Set(1);
    TIM2::CCER::CC2E::Set(1);
    TIM2::DIER::CC2IE::Set(1);
    NVIC::ISER0::SETENA::Set(1u << 28);     
}

void HrSensor::SetExpectedHz(uint16_t Hz)
{
    expectedHz_ = Hz;
    
}

uint16_t HrSensor::SampleFreq() const
{
    
     if (expectedHz_ == 0)
        return freqHz_;

   
    if ( (freqHz_ > expectedHz_ + 1) ||
         (freqHz_ + 1 < expectedHz_) )
        return 0;              

    return freqHz_;
}



void HrSensor::IRQHandler()
{
  if (TIM2::SR::CC2IF::Get())
  {

    const uint32_t dt = TIM2::CCR2::Get();

    auto timerClock = SystemCoreClock / 16U;
   // constexpr auto timerClock = 16000000U/16U;
    float period = static_cast <float>(dt) /static_cast <float>(timerClock);
    freqHz_ = 1/period;

     
    TIM2::SR::CC2IF::Set(0);
  }
}

extern "C" void TIM2_IRQHandler()
{
    HrSensor::IRQHandler();
}