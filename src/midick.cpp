#include "pico/stdlib.h"
#include "../include/button.h"
#include "tusb.h"
#include "bsp/board.h"
#include "hardware/uart.h"

int main() {
    stdio_init_all();
    board_init();
    tusb_init();
    uart_init(uart0, 31250);
    gpio_set_function(0, GPIO_FUNC_UART);

    Button buttons[] = {
                        Button(2, 14, 15, 4, 0),
                        Button(3, 16, 17, 5, 1),
                        Button(4, 20, 21, 6, 2),
                        Button(5, 26, 27, 7, 3)
                        };

    
    while (true) {
        tud_task();
        for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
            buttons[i].update();
        }
    }
}