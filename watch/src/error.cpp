
#include "screen.hpp"
#include "util/display.hpp"

namespace screen {

    void setup_error() {
        loop_current = &loop_error;
        frame_delta = 1000;
    }

    void loop_error() {
        display::g.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        display::g.drawString(
            display::WIDTH / 2, display::HEIGHT / 2, 
            "Unable to get time. :/"
        );
    }

}