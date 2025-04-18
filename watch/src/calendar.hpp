
#pragma once

#include <time.h>
#include <cinttypes>

namespace calendar {

    extern const char* const NTP_SERVER;
    extern const char* const TIME_ZONE;

    void init();
    

    extern tm local_time;

    bool fetch();


    struct Item {
        const char* name;
        uint8_t hour;
        uint8_t minute;

        Item(const char* name, uint8_t hour, uint8_t minute):
            name(name), hour(hour), minute(minute) {}
    };

    struct Schedule {
        const Item* items;
        int item_count;

        Schedule(const Item* items, int item_count):
            items(items), item_count(item_count) {}
    };

    extern const Schedule WEEKDAYS[];

}
