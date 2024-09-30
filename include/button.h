#include "../include/led.h"
class Button{
    private:
        uint pin;

        uint pinLED1;
        uint pinLED2;


        uint8_t longNote;
        uint8_t shortNote;

    public:
        Button(uint pin, uint pinLED1, uint pinLED2, uint8_t longNote, uint8_t shortNote);

        LED led;

        void update();

        void shortPressed();

        void longPressed();

};