#include "pico/stdlib.h"
#include "../include/button.h"
#include "tusb.h"
#include "bsp/board.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

void midi_task(void);

int main()
{

    stdio_init_all();
    
    board_init();

    tusb_init();

    Button button1(5,14,15,90,80);

    while (true) {
        tud_task(); // tinyusb device task
        button1.update();

    }
}


