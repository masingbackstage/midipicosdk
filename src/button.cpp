#include "pico/stdlib.h"     
#include "../include/button.h"
#include "../include/led.h"
#include "tusb.h"
#include "hardware/uart.h"

Button::Button(uint pin, uint pinLED1, uint pinLED2, uint8_t longNote, uint8_t shortNote)
    : pin(pin), pinLED1(pinLED1), pinLED2(pinLED2), led(pinLED1, pinLED2), 
      longNote(longNote), shortNote(shortNote), 
      lastButtonState(false), buttonPressed(false), lastDebounceTime(get_absolute_time())
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

void Button::update() {
    const uint debounceDelay = 50;
    const uint longPressThreshold = 1000;

    bool currentButtonState = gpio_get(pin);

    if (currentButtonState != lastButtonState) {
        lastDebounceTime = get_absolute_time();
    }

    if (absolute_time_diff_us(lastDebounceTime, get_absolute_time()) > debounceDelay * 1000) {
        if (currentButtonState && !buttonPressed) {
            buttonPressed = true;
            pressStartTime = get_absolute_time();
        } 
        else if (!currentButtonState && buttonPressed) {
            buttonPressed = false;
            uint64_t pressDuration = absolute_time_diff_us(pressStartTime, get_absolute_time()) / 1000;
            if (pressDuration >= longPressThreshold) {
                longPressed();
            } else {
                shortPressed();
            }
        }
    }

    lastButtonState = currentButtonState;
    led.update();
}


void Button::longPressed(){
        led.longPress();
        uint8_t msg[3];
        msg[0] = 0x90;                    // Note On - Channel 1
        msg[1] = longNote;                // Note Number
        msg[2] = 127;                     // Velocity
        tud_midi_n_stream_write(0, 0, msg, 3);
        sendUartMsg(msg);
        // Send Note Off for previous note.
        msg[0] = 0x80;                    // Note Off - Channel 1
        msg[1] = longNote;                // Note Number
        msg[2] = 0;                       // Velocity
        tud_midi_n_stream_write(0, 0, msg, 3);
        sendUartMsg(msg);
};

void Button::shortPressed(){
        led.shortPress();
        uint8_t msg[3];
        msg[0] = 0x90;                    // Note On - Channel 1
        msg[1] = shortNote;               // Note Number
        msg[2] = 127;                     // Velocity
        tud_midi_n_stream_write(0, 0, msg, 3);
        sendUartMsg(msg);
        // Send Note Off for previous note.
        msg[0] = 0x80;                    // Note Off - Channel 1
        msg[1] = shortNote;               // Note Number
        msg[2] = 0;                       // Velocity
        tud_midi_n_stream_write(0, 0, msg, 3);
        sendUartMsg(msg);
};

void Button::sendUartMsg(uint8_t msg[3]){
    uart_putc(uart0, msg[0]);
    uart_putc(uart0, msg[1]);
    uart_putc(uart0, msg[2]);
};
