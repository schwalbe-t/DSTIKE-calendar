
#include <Arduino.h>
#include "util/input.hpp"
#include "util/display.hpp"
#include "util/wifi.hpp"
#include "screen.hpp"

void setup() {
    input::init();
    display::init();
    display::g.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display::g.drawString(
        display::WIDTH / 2, display::HEIGHT / 2, 
        "Connecting to network..."
    );
    display::show();
    bool success = wifi::connect_to_any(wifi::NETWORKS, wifi::NETWORK_COUNT);
    calendar::init();
    if(success) { screen::setup_front(); } 
    else { screen::setup_error(); }
}

void loop() {
    input::update();
    if(!calendar::fetch()) { screen::setup_error(); }
    display::clear();
    screen::loop_current();
    display::show();
    delay(screen::frame_delta);
}