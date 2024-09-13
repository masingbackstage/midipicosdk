#include "pico/stdlib.h"
#include "../include/led.h"

LED::LED(uint pin1, uint pin2)
    :pin1(pin1), pin2(pin2)
{
    gpio_init(pin1);
    gpio_set_dir(pin1, GPIO_OUT);
    gpio_init(pin2);
    gpio_set_dir(pin2, GPIO_OUT);
};


void LED::shortPress(){
    if(gpio_get(pin1)){
        gpio_put(pin1, 0);
        gpio_put(pin2, 1);
    }else{
        gpio_put(pin1, 1);
        gpio_put(pin2, 0);
    }
};

void LED::longPress(){
    if (gpio_get(pin1)){
        for (int i = 0; i < count; i++)
        {
            gpio_put(pin1, 0);
            gpio_put(pin2, 1);
            sleep_ms(200);
            gpio_put(pin1, 1);
            gpio_put(pin2, 0);
            sleep_ms(200);
        }
    }
    else{
        for (int i = 0; i < count; i++)
        {
            gpio_put(pin1, 1);
            gpio_put(pin2, 0);
            sleep_ms(200);
            gpio_put(pin1, 0);
            gpio_put(pin2, 1);
            sleep_ms(200);
        }

    }
};
