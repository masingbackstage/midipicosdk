#include "pico/stdlib.h"     
#include "../include/button.h"
#include "../include/led.h"

Button::Button(uint pin, uint pinLED1, uint pinLED2)
    : pin(pin), pinLED1(pinLED1), pinLED2(pinLED2), led(pinLED1, pinLED2)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}


void Button::update(){
        if(gpio_get(pin) && !wasPressed){
                shortBounceMS = get_absolute_time() + shortDurationMS;
                longBounceMS = get_absolute_time() + longDurationMS;
        }
        if (get_absolute_time() > longBounceMS && !gpio_get(pin))
                longPressed();
        else if (get_absolute_time() > shortBounceMS && !gpio_get(pin))
                shortPressed();
        wasPressed = gpio_get(pin);
};


void Button::longPressed(){
        //led.longPress();
};

void Button::shortPressed(){
        led.shortPress();
};