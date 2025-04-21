
#include "screen.hpp"
#include "util/display.hpp"
#include "util/input.hpp"
#include <optional>
#include <utility>

namespace screen {

    static std::pair<int, char> display_period(int64_t secs) {
        int days = (int) (secs / calendar::SECS_PER_DAY);
        if(days >= 1) { return { days, 'd' }; }
        int hours = (int) (secs / calendar::SECS_PER_HOUR) % 24;
        if(hours >= 1) { return { hours, 'h' }; }
        int mins = (int) (secs / calendar::SECS_PER_MIN) % 60;
        if(mins >= 1) { return { mins, 'm' }; }
        return { secs, 's' };
    }

    static void draw_weekday(int y, const tm& day_date) {
        if(y + display::LINE_HEIGHT < 0 || y > display::HEIGHT) { return; }
        display::g.setColor(WHITE);
        display::g.fillRect(0, y, display::WIDTH, 12);
        display::g.setColor(BLACK);
        display::g.setTextAlignment(TEXT_ALIGN_LEFT);
        display::g.drawString(2, y, WEEKDAY_NAMES[calendar::wday_of(day_date)]);
        display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
        draw_date_long(display::WIDTH - 2, y, day_date);
        display::g.setColor(WHITE);
    }

    static void draw_item_summary(
        int y, const calendar::Item& item, const tm& day_date
    ) {
        if(y + display::LINE_HEIGHT < 0 || y > display::HEIGHT) { return; }
        display::g.setTextAlignment(TEXT_ALIGN_LEFT);
        display::g.drawString(0, y, item.name);
        tm start_date = calendar::start_date_of(item, day_date);
        tm end_date = calendar::end_date_of(item, day_date);
        time_t start_time = mktime(&start_date);
        time_t end_time = mktime(&end_date);
        int64_t period_secs = (int64_t) end_time - (int64_t) start_time;
        auto [count, unit] = display_period(period_secs);
        display::g.setTextAlignment(TEXT_ALIGN_RIGHT);
        display::g.drawStringf(
            display::WIDTH, y, fmt_buffer, 
            "%d%c  %02d:%02d", 
            count, unit,
            start_date.tm_hour, start_date.tm_min
        );
    }

    const time_t MAX_ITEM_REMAINING_TIME = calendar::SECS_PER_DAY * 7;
    const float SCROLL_SPEED = (20.0 / 1000.0) // every 20ms
        * ((float) display::HEIGHT * 3.0); // three full screens
         
    float offset;

    void setup_list() {
        loop_current = &loop_list;
        frame_delta = 20;
        offset = 0.0;
    }

    void loop_list() {
        if(input::was_pressed(input::Push)) { screen::setup_front(); }
        time_t local_time = mktime(&calendar::local_time);
        time_t stop_after = local_time + MAX_ITEM_REMAINING_TIME;
        auto items = calendar::Upcoming::after(calendar::local_time);
        std::optional<tm> last_day_date = std::nullopt;
        int y = (int) offset;
        for(;;) {
            const calendar::Item* item = items.next();
            if(item == nullptr) { break; }
            time_t day_start_time = mktime(&items.day_date);
            if(day_start_time > stop_after) { break; }
            bool new_day = !last_day_date.has_value()
                || mktime(&*last_day_date) < mktime(&items.day_date);
            if(new_day) {
                if(last_day_date.has_value()) { y += display::LINE_HEIGHT; }
                draw_weekday(y, items.day_date);
                y += display::LINE_HEIGHT;
            }
            last_day_date = items.day_date;
            draw_item_summary(y, *item, items.day_date);
            y += display::LINE_HEIGHT;
        }
        int height = y - ((int) offset);
        float max_offset = height - display::HEIGHT;
        if(input::is_down(input::Up)) {
            offset += SCROLL_SPEED;
        }
        if(input::is_down(input::Down)) {
            offset -= SCROLL_SPEED;
        }
        offset = std::min(offset, (float) 0.0);
        offset = std::max(offset, -max_offset);
    }

}