
#include "screen.hpp"
#include "util/display.hpp"
#include "util/input.hpp"

namespace screen {

    void draw_remaining_time_long(int x, int y, int64_t r_secs) {
        int r_days = (int) (r_secs / calendar::SECS_PER_DAY);
        int r_hours = (int) (r_secs / calendar::SECS_PER_HOUR) % 24;
        int r_mins = (int) (r_secs / calendar::SECS_PER_MIN) % 60;
        if(r_days >= 1) {
            display::g.drawStringf(
                x, y, fmt_buffer, 
                "%02dd %02dh %02dm", 
                r_days, r_hours, r_mins
            );
        } else if(r_hours >= 1) {
            display::g.drawStringf(
                x, y, fmt_buffer, 
                "%02dh %02dm %02ds", 
                r_hours, r_mins, (int) r_secs % 60
            );
        } else if(r_mins >= 1) {
            display::g.drawStringf(
                x, y, fmt_buffer, 
                "%02dm %02ds", 
                r_mins, (int) r_secs % 60
            );
        } else {
            display::g.drawStringf(
                x, y, fmt_buffer, 
                "%02ds", 
                (int) r_secs % 60
            );
        }
    }

    static const char* const IN_PROGRESS = "in progress";

    void draw_item(
        int y, const calendar::Item& item, const tm& day_date
    ) {
        display::g.setTextAlignment(TEXT_ALIGN_LEFT);
        display::g.drawString(0, y, item.name);
        display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
        display::g.drawStringf(
            display::WIDTH, y, fmt_buffer, 
            "%s %d.",
            WEEKDAY_NAMES_SHORT[calendar::wday_of(day_date)], 
            (int) day_date.tm_mday
        );
        y += display::LINE_HEIGHT;
        tm start_date = calendar::start_date_of(item, day_date);
        tm end_date = calendar::end_date_of(item, day_date);
        time_t local_time = mktime(&calendar::local_time);
        time_t start_time = mktime(&start_date);
        time_t end_time = mktime(&end_date);
        bool in_progress = local_time > start_time;
        int64_t r_secs = (int64_t) (in_progress? end_time : start_time) 
            - (int64_t) local_time;
        display::g.setTextAlignment(TEXT_ALIGN_LEFT);
        draw_remaining_time_long(0, y, r_secs);
        display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
        if(in_progress) {
            display::g.drawString(display::WIDTH, y, IN_PROGRESS);
        } else {
            draw_time_short(display::WIDTH, y, start_date);
        }
    }

    static const int DISPLAYED_ITEMS_VERT_START = 14;
    static const int DISPLAYED_ITEM_OFFSET = display::LINE_HEIGHT * 2;
    static const int DISPLAYED_ITEM_PADDING = 2;

    void setup_front() {
        loop_current = &loop_front;
        frame_delta = 200;
    }

    void loop_front() {
        if(input::was_pressed(input::Push)) { screen::setup_list(); }
        display::g.setColor(WHITE);
        display::g.fillRect(0, 0, display::WIDTH, 12);
        display::g.setColor(BLACK);
        display::g.setTextAlignment(TEXT_ALIGN_LEFT);
        draw_time_long(2, 0, calendar::local_time);
        display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
        draw_date_long(display::WIDTH - 2, 0, calendar::local_time);
        display::g.setColor(WHITE);
        time_t local_time = mktime(&calendar::local_time);
        auto items = calendar::Upcoming::after(calendar::local_time);
        int y = DISPLAYED_ITEMS_VERT_START;
        while(y + DISPLAYED_ITEM_OFFSET <= display::HEIGHT) {
            const calendar::Item* item = items.next();
            if(item == nullptr) { break; }
            tm item_date = calendar::end_date_of(*item, items.day_date);
            time_t item_time = mktime(&item_date);
            if(local_time > item_time) { continue; }
            draw_item(y, *item, items.day_date);
            y += DISPLAYED_ITEM_OFFSET + DISPLAYED_ITEM_PADDING;
        }
    }

}