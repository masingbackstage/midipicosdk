#pragma once
class LED
{
private:
        uint pin1, pin2;
        const int count = 4;
public:
    LED(uint pin1, uint pin2);

    void shortPress();

    void longPress();

};