
#pragma once

#include <time.h>
#include <cinttypes>

namespace calendar {

    extern const int64_t SECS_PER_MIN;
    extern const int64_t SECS_PER_HOUR;
    extern const int64_t SECS_PER_DAY;


    extern const char* const NTP_SERVER;
    extern const char* const TIME_ZONE;

    void init();
    

    extern tm local_time;

    bool fetch();


    struct Item {
        const char* name;
        uint8_t start_hour;
        uint8_t start_minute;
        uint8_t end_hour;
        uint8_t end_minute;

        Item(
            const char* name, 
            uint8_t start_hour, uint8_t start_minute,
            uint8_t end_hour, uint8_t end_minute
        ): name(name), start_hour(start_hour), start_minute(start_minute),
            end_hour(end_hour), end_minute(end_minute) {}
    };

    struct Schedule {
        const Item* items;
        int item_count;

        Schedule(const Item* items, int item_count):
            items(items), item_count(item_count) {}
    };

    extern const Schedule WEEKDAYS[];


    struct Upcoming {
        tm day_date;
        int item_i;

        static Upcoming after(tm start_date);

        const Item* next();
    };


    tm date_after(tm date, time_t delay_seconds);

    tm start_date_of(const Item& item, const tm& day_date);
    tm end_date_of(const Item& item, const tm& day_date);

    int wday_of(const tm& day_date);

}
