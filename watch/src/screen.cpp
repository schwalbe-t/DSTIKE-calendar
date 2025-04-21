
#include "screen.hpp"
#include "util/display.hpp"

namespace screen {

    void (*loop_current)();
    int frame_delta;
    char fmt_buffer[128];


    const char* const WEEKDAY_NAMES[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
        "Saturday", "Sunday"
    };

    const char* const WEEKDAY_NAMES_SHORT[] = {
        "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
    };


    void draw_time_short(int x, int y, const tm& date) {
        display::g.drawStringf(
            x, y, fmt_buffer, 
            "%02d:%02d", 
            date.tm_hour, date.tm_min
        );
    }

    void draw_time_long(int x, int y, const tm& date) {
        display::g.drawStringf(
            x, y, fmt_buffer, 
            "%02d:%02d:%02d", 
            date.tm_hour, date.tm_min, date.tm_sec
        );
    }

    void draw_date_long(int x, int y, const tm& date) {
        display::g.drawStringf(
            x, y, fmt_buffer, 
            "%02d.%02d.%04d", 
            date.tm_mday,
            date.tm_mon + 1,
            date.tm_year + 1900
        );
    }

}