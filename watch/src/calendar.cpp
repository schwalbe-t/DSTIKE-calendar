
#include "calendar.hpp"
#include <time.h>
#include <Arduino.h>

namespace calendar {

    const char* const NTP_SERVER = "ch.pool.ntp.org";
    // refer to https://remotemonitoringsystems.ca/time-zone-abbreviations.php
    const char* const TIME_ZONE = "EET-2EEST-3,M3.5.0/03:00:00,M10.5.0/04:00:00";


    void init() {
        setenv("TZ", TIME_ZONE, 1);
        configTime(0, 0, NTP_SERVER);
    }


    tm local_time;

    bool fetch() {
        return getLocalTime(&local_time);
    }


    static const Item MONDAY[] = {
        Item("Class",        8,00),
        Item("Long Break",   8,40),
        Item("Maths",        9,00),
        Item("Short Break",  9,40),
        Item("Art",          9,50),
        Item("Long Break",  10,30),
        Item("History",     10,50),
        Item("Short Break", 11,30),
        Item("Gr. Design",  11,40),
        Item("Short Break", 12,20),
        Item("French",      12,30),
        Item("Short Break", 13,10),
        Item("Chemistry",   13,20),
        Item("End",         14,00)
    };
    static const Item TUESDAY[] = {
        Item("PE",           8,00),
        Item("Long Break",   8,40),
        Item("Biology",      9,00),
        Item("Short Break",  9,40),
        Item("ICT",          9,50),
        Item("Long Break",  10,30),
        Item("Maths",       10,50),
        Item("Short Break", 11,30),
        Item("Philosophy",  11,40),
        Item("Short Break", 12,20),
        Item("Gr. Design",  12,30),
        Item("End",         13,10)
    };
    static const Item WEDNESDAY[] = {
        Item("English",      8,00),
        Item("Long Break",   8,40),
        Item("Economics",    9,00),
        Item("Short Break",  9,40),
        Item("Biology",      9,50),
        Item("Long Break",  10,30),
        Item("Geography",   10,50),
        Item("Short Break", 11,30),
        Item("Physics",     11,40),
        Item("Short Break", 12,20),
        Item("Chemistry",   12,30),
        Item("Short Break", 13,10),
        Item("History",     13,20),
        Item("End",         14,00)
    };
    static const Item THURSDAY[] = {
        Item("Bulgarian",     8,00),
        Item("Long Break",    8,40),
        Item("Bulgarian",     9,00),
        Item("Short Break",   9,40),
        Item("Physics",       9,50),
        Item("Long Break",   10,30),
        Item("Co. Graphics", 10,50),
        Item("Short Break",  11,30),
        Item("History",      11,40),
        Item("Short Break",  12,20),
        Item("Geography",    12,30),
        Item("Short Break",  13,10),
        Item("Drawing",      13,20),
        Item("End",          14,00)
    };
    static const Item FRIDAY[] = {
        Item("French",       8,00),
        Item("Long Break",   8,40),
        Item("PE",           9,00),
        Item("Short Break",  9,40),
        Item("Bulgarian",    9,50),
        Item("Long Break",  10,30),
        Item("English",     10,50),
        Item("Short Break", 11,30),
        Item("Philosophy",  11,40),
        Item("Short Break", 12,20),
        Item("Geography",   12,30),
        Item("End",         13,10)
    };
    static const Item SATURDAY[] = {};
    static const Item SUNDAY[] = {};

    const Schedule WEEKDAYS[] = {
        Schedule(MONDAY, sizeof(MONDAY) / sizeof(Item)),
        Schedule(TUESDAY, sizeof(TUESDAY) / sizeof(Item)),
        Schedule(WEDNESDAY, sizeof(WEDNESDAY) / sizeof(Item)),
        Schedule(THURSDAY, sizeof(THURSDAY) / sizeof(Item)),
        Schedule(FRIDAY, sizeof(FRIDAY) / sizeof(Item)),
        Schedule(SATURDAY, sizeof(SATURDAY) / sizeof(Item)),
        Schedule(SUNDAY, sizeof(SUNDAY) / sizeof(Item))
    };

}