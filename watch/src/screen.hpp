
#pragma once

#include "util/calendar.hpp"

namespace screen {

    extern void (*loop_current)();
    extern int frame_delta;

    extern char fmt_buffer[128];

    extern const char* const WEEKDAY_NAMES[];
    extern const char* const WEEKDAY_NAMES_SHORT[];

    void draw_time_short(int x, int y, const tm& date);
    void draw_time_long(int x, int y, const tm& date);
    void draw_date_long(int x, int y, const tm& date);

    void setup_error();
    void setup_front();
    void setup_list();

    void loop_error();
    void loop_front();
    void loop_list();

}