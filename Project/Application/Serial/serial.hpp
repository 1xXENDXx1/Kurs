#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <cstdint>
#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "usart1registers.hpp"
#include "system_config.hpp"

class Serial {
public:
    static void Init();
    static int  Write(const char* p, int len);
};

extern "C" int _write(int, char*, int);   

#endif 