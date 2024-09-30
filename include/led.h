#pragma once
class LED
{
private:
        uint pin1, pin2;
        const int count = 4;
        bool isBlinking;
        uint blinkCount;
        uint blinkInterval;
        absolute_time_t lastBlinkTime;
        bool lastState;
public:
    LED(uint pin1, uint pin2);

    void shortPress();

    void longPress();

    void update();

};