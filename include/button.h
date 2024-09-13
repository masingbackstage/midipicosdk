#include "../include/led.h"
class Button{
    private:
        uint pin;
        uint pinLED1;
        uint pinLED2;
        const absolute_time_t shortDurationMS = 250;
        const absolute_time_t longDurationMS = 500;
        absolute_time_t shortBounceMS;
        absolute_time_t longBounceMS;
        bool wasPressed = false;

        LED led;

    public:
        Button(uint pin, uint pinLED1, uint pinLED2);

        void update();

        void shortPressed();

        void longPressed();

};