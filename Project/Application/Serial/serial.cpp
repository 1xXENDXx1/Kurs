#include "serial.hpp"

void Serial::Init()
{
    RCC::AHB1ENR::GPIOAEN::Enable::Set();

    GPIOA::MODER ::MODER9 ::Alternate::Set();
    GPIOA::AFRH  ::AFRH9  ::Af7      ::Set();   // USART1_TX
    GPIOA::OSPEEDR::OSPEEDR9::HighSpeed::Set();

    RCC::APB2ENR::USART1EN::Enable::Set();
    USART1::BRR::Write(SystemCoreClock / 115'200U);
    USART1::CR1::TE::Set(1);
    USART1::CR1::UE::Set(1);
}

int Serial::Write(const char* p, int len)
{
    for (int i = 0; i < len; ++i) {
        while (!USART1::SR::TXE::Get()) {}
        USART1::DR::Write(p[i]);
    }
    return len;
}

extern "C" int _write(int, char* p, int len)
{
    return Serial::Write(p, len);
}