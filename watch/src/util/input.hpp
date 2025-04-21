
#pragma once

namespace input {

    enum Button {
        Up, Down, Push
    };


    void init();
    void update();


    bool is_down(Button button);
    bool was_pressed(Button button);

}