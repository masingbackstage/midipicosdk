#include "../include/led.h"
class Button{
    private:
        uint pin;
        uint pinLED1;
        uint pinLED2;
        LED led;

        uint8_t longNote;
        uint8_t shortNote;

        bool lastButtonState;
        bool buttonPressed;
        absolute_time_t pressStartTime;
        absolute_time_t lastDebounceTime;

    public:
        Button(uint pin, uint pinLED1, uint pinLED2, uint8_t longNote, uint8_t shortNote);
        void update();
        void shortPressed();
        void longPressed();
};