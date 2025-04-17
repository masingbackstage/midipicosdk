#include "pico/stdlib.h"
#include "../include/button.h"
#include "tusb.h"
#include "bsp/board.h"
#include "hardware/uart.h"

int main() {
    board_init();
    tusb_init();
    stdio_init_all();
    uart_init(uart0, 31250);
    gpio_set_function(0, GPIO_FUNC_UART);
    int whichMode = 0;
    int whichPressed = -1;

    Button buttons[] = {
                        Button(2, 14, 15, 4, 0),
                        Button(3, 16, 17, 5, 1),
                        Button(4, 20, 21, 6, 2),
                        Button(5, 26, 27, 7, 3)
                        };

    for(int i = 0; i < 2; i++) {
        for(Button button : buttons) {
            button.led.setPins(0,1);
            sleep_ms(100);
        }
        for(Button button : buttons) {
            button.led.setPins(1,0);
            sleep_ms(100);
        }
    }

    for (Button button : buttons)
    {
        button.led.setPins(0, 0);
        sleep_ms(100);
    }

    if(buttons[0].getPin()) whichMode = 1;

    if (buttons[3].getPin())
    {
        whichMode = 2;
        for(Button button : buttons) {
            button.led.setPins(0,1);
        }
    }

    while (true) {
        tud_task();
        if (whichMode == 1) {
            for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
                if (buttons[i].updateCortex()) {
                    whichPressed = i;
                }
                if(whichPressed != i) {
                    buttons[i].led.setPins(1,1);
                }
            }
        } else if(whichMode == 2){
            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
                buttons[i].update();
            }
        } else if (whichMode == 0) {
            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
                if (buttons[i].updatePullIn()) {
                    whichPressed = i;
                }
                if(whichPressed != i) {
                    buttons[i].led.setPins(1,1);
                }
            }
        }
    }
}