
#include <Arduino.h>
#include "display.hpp"
#include "wifi.hpp"
#include "calendar.hpp"

void setup() {
    display::init();
    display::g.setTextAlignment(TEXT_ALIGN_LEFT);
    display::g.drawString(0, 0, "Connecting to network...");
    display::show();
    wifi::connect_to_any(wifi::NETWORKS, wifi::NETWORK_COUNT);
    calendar::init();
}

const int DISPLAYED_ITEMS_VERT_START = 16;
const int DISPLAYED_ITEM_HEIGHT = 12;
const int MAX_DISPLAYED_ITEM_COUNT = 4;
const int64_t SECONDS_PER_MINUTE = 60;
const int64_t SECONDS_PER_HOUR = SECONDS_PER_MINUTE * 60;
const int64_t SECONDS_PER_DAY = SECONDS_PER_HOUR * 24;
char fmt_buffer[256];

static tm date_after_seconds(tm date, int64_t offset) {
    time_t time = mktime(&date);
    time += offset;
    tm result;
    localtime_r(&time, &result);
    return result;
}

void loop() {
    calendar::fetch();
    display::clear();
    display::g.setColor(WHITE);
    display::g.fillRect(0, 0, display::WIDTH, 12);
    display::g.setColor(BLACK);
    display::g.setTextAlignment(TEXT_ALIGN_LEFT);
    display::g.drawStringf(
        2, 0, fmt_buffer, 
        "%02d:%02d:%02d", 
        calendar::local_time.tm_hour, 
        calendar::local_time.tm_min, 
        calendar::local_time.tm_sec
    );
    display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
    display::g.drawStringf(
        display::WIDTH - 2, 0, fmt_buffer, 
        "%02d.%02d.%04d", 
        calendar::local_time.tm_mday,
        calendar::local_time.tm_mon + 1,
        calendar::local_time.tm_year + 1900
    );
    display::g.setColor(WHITE);
    time_t local_time = mktime(&calendar::local_time);
    int displayed_items = 0;
    for(int d = 0; d < 7; d += 1) {
        int wday = calendar::local_time.tm_wday;
        wday = wday == 0? 6 : wday - 1; // tm_wday = 0 => Sunday
        wday = (wday + d) % 7;
        tm day_date = date_after_seconds(
            calendar::local_time, d * SECONDS_PER_DAY
        );
        const calendar::Schedule& schedule = calendar::WEEKDAYS[wday];
        for(int i = 0; i < schedule.item_count; i += 1) {
            const calendar::Item& item = schedule.items[i];
            tm item_date = day_date;
            item_date.tm_sec = 0;
            item_date.tm_min = item.minute;
            item_date.tm_hour = item.hour;
            time_t item_time = mktime(&item_date);
            if(local_time > item_time) { continue; }
            int64_t r_secs = (int64_t) item_time - (int64_t) local_time;
            int r_days = (int) (r_secs / SECONDS_PER_DAY);
            int r_hours = (int) (r_secs / SECONDS_PER_HOUR) % 24;
            int r_mins = (int) (r_secs / SECONDS_PER_MINUTE) % 60;
            int item_vert_pos = DISPLAYED_ITEMS_VERT_START 
                + displayed_items * DISPLAYED_ITEM_HEIGHT;
            display::g.setTextAlignment(TEXT_ALIGN_LEFT);
            display::g.drawString(0, item_vert_pos, item.name);
            display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
            display::g.drawStringf(
                display::WIDTH, item_vert_pos, fmt_buffer, 
                "%02d:%02d (-%02d%c)", 
                item_date.tm_hour,
                item_date.tm_min,
                (r_days >= 1? r_days : r_hours >= 1? r_hours : r_mins),
                (r_days >= 1? 'd' : r_hours >= 1? 'h' : 'm')
            );
            displayed_items += 1;
            if(displayed_items >= MAX_DISPLAYED_ITEM_COUNT) { break; }
        }
    }
    display::show();
    delay(500);
}