#include "../include/led.h"
class Button{
    private:
        uint pin;
        uint pinLED1;
        uint pinLED2;
        

        uint8_t longProgram;
        uint8_t shortProgram;

        bool lastButtonState;
        bool buttonPressed;
        absolute_time_t pressStartTime;
        absolute_time_t lastDebounceTime;

        bool isPressed = false;

    public:
        LED led;

        Button(uint pin, uint pinLED1, uint pinLED2, uint8_t longProgram, uint8_t shortProgram);

        bool update();

        void shortPressed();
        
        void longPressed();

        void sendUartMsg(uint8_t msg[3]);

        bool updateCortex();

        bool getPin();
};