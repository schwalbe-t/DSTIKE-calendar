
#include "display.hpp"

namespace display {

    // display type: SH1106 1.3" OLED display
    // pin definitions for I2C connected OLED display
    const uint8_t ADDRESS = 0x3C;
    const int SDA_PIN = D1; // pin 5
    const int SCL_PIN = D2; // pin 4
    const int WIDTH = 128;
    const int HEIGHT = 64;
    const int LINE_HEIGHT = 12;

    SH1106Wire g = SH1106Wire(ADDRESS, SDA_PIN, SCL_PIN);
    

    void init() {
        g.init();
        g.flipScreenVertically();
        g.setFont(ArialMT_Plain_10);
        g.displayOn();
        clear();
        show();
    }

    void clear() { g.clear(); }

    void show() { g.display(); }

}