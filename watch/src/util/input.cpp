
#include "input.hpp"
#include <Arduino.h>
#include <cstring>

namespace input {

    struct ButtonState {
        const int pin;
        bool is_pressed;
        bool was_pressed;

        ButtonState(int pin): pin(pin), is_pressed(false), was_pressed(false) {}
    };

    ButtonState buttons[] = {
        // number of elems in 'input::Button'
        ButtonState(12), // Up
        ButtonState(13), // Down
        ButtonState(14), // Push
    };
    const int BUTTON_COUNT = sizeof(buttons) / sizeof(ButtonState);

    void init() {
        for(const ButtonState& button: buttons) {
            pinMode(button.pin, INPUT_PULLUP);
        }
    }

    void update() {
        for(ButtonState& button: buttons) {
            button.was_pressed = button.is_pressed;
            button.is_pressed = !digitalRead(button.pin);
        }
    }


    bool is_down(Button button) {
        return buttons[(int) button].is_pressed;
    }

    bool was_pressed(Button button) {
        const ButtonState& b = buttons[(int) button];
        return !b.was_pressed && b.is_pressed;
    }

}