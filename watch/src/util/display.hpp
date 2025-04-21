
#pragma once

#include <SH1106Wire.h>

namespace display {

    extern const int WIDTH;
    extern const int HEIGHT;
    extern const int LINE_HEIGHT;

    extern SH1106Wire g;

    void init();
    void clear();
    void show();

}