#include "pico/stdlib.h"
#include "../include/button.h"
#include "tusb.h"
#include "bsp/board.h"


int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    Button buttons[] = {
                        Button(5, 14, 15, 1, 2),
                        Button(6, 16, 17, 3, 4),
                        Button(7, 18, 19, 5, 6),
                        Button(8, 20, 21, 7, 8)
                        };


    while (true) {
        tud_task();
        for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
        {
            buttons[i].update();
        }
    }
}