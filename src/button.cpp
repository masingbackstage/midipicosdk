#include "pico/stdlib.h"     
#include "../include/button.h"
#include "../include/led.h"

Button::Button(uint pin, uint pinLED1, uint pinLED2)
    : pin(pin), pinLED1(pinLED1), pinLED2(pinLED2), led(pinLED1, pinLED2)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}
void Button::update() {
    static bool lastButtonState = false;
    static bool buttonPressed = false;
    static absolute_time_t pressStartTime;
    static absolute_time_t lastDebounceTime = get_absolute_time();
    const uint debounceDelay = 50;
    const uint longPressThreshold = 1000;

    bool currentButtonState = gpio_get(pin);

    if (currentButtonState != lastButtonState) {
        lastDebounceTime = get_absolute_time();
    }

    if (absolute_time_diff_us(lastDebounceTime, get_absolute_time()) > debounceDelay * 1000) {
        if (currentButtonState && !buttonPressed) {
            buttonPressed = true;
            pressStartTime = get_absolute_time();
        } 
        else if (!currentButtonState && buttonPressed) {
            buttonPressed = false;
            uint64_t pressDuration = absolute_time_diff_us(pressStartTime, get_absolute_time()) / 1000;
            if (pressDuration >= longPressThreshold) {
                longPressed();
            } else {
                shortPressed();
            }
        }
    }

    lastButtonState = currentButtonState;
}

void Button::longPressed(){
        led.longPress();
};

void Button::shortPressed(){
        led.shortPress();
};