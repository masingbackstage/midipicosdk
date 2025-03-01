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
    bool isCortex = true;
    int whichPressed = -1;

    Button buttons[] = {
                        Button(2, 14, 15, 4, 0),
                        Button(3, 16, 17, 5, 1),
                        Button(4, 20, 21, 6, 2),
                        Button(5, 26, 27, 7, 3)
                        };

    if(buttons[3].getPin()) isCortex = false;
    
    while (true) {
        tud_task();
        if (isCortex) {
            for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
                if (buttons[i].updateCortex()) {
                    whichPressed = i;
                }
                if(whichPressed != i) {
                    buttons[i].led.setPins(1,1);
                }
            }
        } else {
            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
                buttons[i].update();
            }
        }
    }
}