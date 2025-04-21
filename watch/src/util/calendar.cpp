
#include "calendar.hpp"
#include <time.h>
#include <Arduino.h>

namespace calendar {

    const int64_t SECS_PER_MIN = 60;
    const int64_t SECS_PER_HOUR = SECS_PER_MIN * 60;
    const int64_t SECS_PER_DAY = SECS_PER_HOUR * 24;


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
        Item("1. Class",         8,00,  8,40),
        Item("2. Maths",         9,00,  9,40),
        Item("3. Art",           9,50, 10,30),
        Item("4. History",      10,50, 11,30),
        Item("5. Gr. Design",   11,40, 12,20),
        Item("6. French",       12,30, 13,10),
        Item("7. Chemistry",    13,20, 14,00)
    };
    static const Item TUESDAY[] = {
        Item("1. PE",            8,00,  8,40),
        Item("2. Biology",       9,00,  9,40),
        Item("3. ICT",           9,50, 10,30),
        Item("4. Maths",        10,50, 11,30),
        Item("5. Philosophy",   11,40, 12,20),
        Item("6. Gr. Design",   12,30, 13,10)
    };
    static const Item WEDNESDAY[] = {
        Item("1. English",       8,00,  8,40),
        Item("2. Economics",     9,00,  9,40),
        Item("3. Biology",       9,50, 10,30),
        Item("4. Geography",    10,50, 11,30),
        Item("5. Physics",      11,40, 12,20),
        Item("6. Chemistry",    12,30, 13,10),
        Item("7. History",      13,20, 14,00)
    };
    static const Item THURSDAY[] = {
        Item("1. Bulgarian",     8,00,  8,40),
        Item("2. Bulgarian",     9,00,  9,40),
        Item("3. Physics",       9,50, 10,30),
        Item("4. Co. Graphics", 10,50, 11,30),
        Item("5. History",      11,40, 12,20),
        Item("6. Geography",    12,30, 13,10),
        Item("7. Drawing",      13,20, 14,00)
    };
    static const Item FRIDAY[] = {
        Item("1. French",        8,00,  8,40),
        Item("2. PE",            9,00,  9,40),
        Item("3. Bulgarian",     9,50, 10,30),
        Item("4. English",      10,50, 11,30),
        Item("5. Philosophy",   11,40, 12,20),
        Item("6. Geography",    12,30, 13,10)
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


    Upcoming Upcoming::after(tm start_date) {
        Upcoming coming;
        coming.day_date = start_date;
        coming.day_date.tm_sec = 0;
        coming.day_date.tm_min = 0;
        coming.day_date.tm_hour = 0;
        coming.item_i = 0;
        return coming;
    }

    const Item* Upcoming::next() {
        for(int i = 0;; i += 1) {
            if(i >= 100) { return nullptr; }
            const Schedule& schedule = WEEKDAYS[wday_of(this->day_date)];
            if(this->item_i < schedule.item_count) { break; }
            item_i = 0;
            this->day_date = date_after(this->day_date, SECS_PER_DAY);
        }
        const Schedule& schedule = WEEKDAYS[wday_of(this->day_date)];
        const Item* item = &schedule.items[this->item_i];
        this->item_i += 1;
        return item;
    }


    tm date_after(tm date, time_t delay) {
        time_t time = mktime(&date);
        time += delay;
        tm result;
        localtime_r(&time, &result);
        return result;
    }


    tm start_date_of(const Item& item, const tm& day_date) {
        tm item_date = day_date;
        item_date.tm_sec = 0;
        item_date.tm_min = item.start_minute;
        item_date.tm_hour = item.start_hour;
        return item_date;
    }
    
    tm end_date_of(const Item& item, const tm& day_date) {
        tm item_date = day_date;
        item_date.tm_sec = 0;
        item_date.tm_min = item.end_minute;
        item_date.tm_hour = item.end_hour;
        return item_date;
    }


    int wday_of(const tm& day_date) {
        // tm_wday is 0-indexed, starting at Sunday
        // however, we need it to start at Monday :)
        return (day_date.tm_wday + 7 - 1) % 7;
    }

}