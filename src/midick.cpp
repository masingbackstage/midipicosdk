#include "pico/stdlib.h"
#include "../include/button.h"
#include "tusb.h"
#include "bsp/board.h"


int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    Button buttons[] = {
                        Button(2, 16, 17, 1, 2),
                        Button(3, 18, 19, 3, 4),
                        Button(4, 20, 21, 5, 6),
                        Button(5, 26, 27, 7, 8)
                        };


    while (true) {
        tud_task();
        for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
        {
            buttons[i].update();
        }
    }
}