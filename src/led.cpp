#include "pico/stdlib.h"
#include "../include/led.h"

LED::LED(uint pin1, uint pin2)
    : pin1(pin1), pin2(pin2), isBlinking(false), blinkCount(0), blinkInterval(200) {
    gpio_init(pin1);
    gpio_set_dir(pin1, GPIO_OUT);
    gpio_init(pin2);
    gpio_set_dir(pin2, GPIO_OUT);
    gpio_put(pin1, 1);
    gpio_put(pin2, 0);
    lastBlinkTime = get_absolute_time();
};

void LED::shortPress(){
    bool newState = !gpio_get(pin1);
    gpio_put(pin1, newState);
    gpio_put(pin2, !newState);
};

void LED::longPress(){
    blinkCount = 4 * 2;  
    isBlinking = true;   
    lastBlinkTime = get_absolute_time();
    lastState = gpio_get(pin1);
}

void LED::update(){
    if (isBlinking) {
        if (absolute_time_diff_us(lastBlinkTime, get_absolute_time()) >= blinkInterval * 1000) {
            gpio_put(pin1, !gpio_get(pin1));
            gpio_put(pin2, !gpio_get(pin2));

            lastBlinkTime = get_absolute_time();
            blinkCount--;

            if (blinkCount <= 0) {
                isBlinking = false;
                gpio_put(pin1, lastState);
                gpio_put(pin2, !lastState);
            }
        }
    }
}
