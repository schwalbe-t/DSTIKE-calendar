
#pragma once

#include <SH1106Wire.h>

namespace display {

    extern const uint8_t ADDRESS;
    extern const int SDA_PIN;
    extern const int SCL_PIN;
    extern const uint32_t WIDTH;
    extern const uint32_t HEIGHT;

    extern SH1106Wire g;

    void init();
    void clear();
    void show();

}