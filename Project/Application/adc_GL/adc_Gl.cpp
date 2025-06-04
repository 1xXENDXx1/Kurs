#include "adc_Gl.hpp"

Adc::Adc(uint8_t ch) : mCh(ch) {}

void Adc::Init()
{
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();

    RCC::APB2ENR::ADC1EN::Enable::Set();

    ADC1::CR2::ADON ::Disable::Set();
    ADC1::CR1::RES  ::Bits12 ::Set();
    ADC1::CR2::EOCS ::SingleConversion::Set();
    ADC1::CR2::CONT ::SingleConversion::Set();
    ADC1::SQR1::L   ::Conversions1::Set();
    ADC1::SQR3::SQ1 ::Set(mCh);

    uint32_t sm = ADC1::SMPR2::Get();
    sm &= ~(0b111u << (3 * mCh));
    sm |=  (0b100u << (3 * mCh));   // 84 cycles
    ADC1::SMPR2::Set(sm);

    ADC1::CR2::ADON::Enable::Set();
}

uint16_t Adc::Sample()
{
    ADC1::CR2::SWSTART::On::Set();
    while (!ADC1::SR::EOC::ConversionComplete::IsSet()) {}
    return static_cast<uint16_t>(ADC1::DR::DATA::Get());
}