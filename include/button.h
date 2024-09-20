#include "../include/led.h"
class Button{
    private:
        uint pin;
        uint pinLED1;
        uint pinLED2;

        LED led;

    public:
        Button(uint pin, uint pinLED1, uint pinLED2);

        void update();

        void shortPressed();

        void longPressed();

};