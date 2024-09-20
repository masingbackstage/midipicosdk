#include "pico/stdlib.h"
#include "../include/button.h"

int main()
{
    stdio_init_all();



    Button button1(5,14,15);
    while (true) {
        button1.update();
    }
}
