#include "pico/stdlib.h"
#include "../include/button.h"
#include "../include/led.h"
#include "tusb.h"
#include "hardware/uart.h"

Button::Button(
  uint pin,
  uint pinLED1,
  uint pinLED2,
  uint8_t longProgram,
  uint8_t shortProgram
)
  : pin(pin),
    pinLED1(pinLED1),
    pinLED2(pinLED2),
    led(pinLED1, pinLED2),
    longProgram(longProgram),
    shortProgram(shortProgram),
    lastButtonState(false),
    buttonPressed(false),
    lastDebounceTime(get_absolute_time()) {
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
}

bool Button::update() {
  const uint debounceDelay = 50;
  const uint longPressThreshold = 500;
  isPressed = false;

  bool currentButtonState = gpio_get(pin);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = get_absolute_time();
  }

  if (absolute_time_diff_us(lastDebounceTime, get_absolute_time()) >
      debounceDelay * 1000) {
    if (currentButtonState && !buttonPressed) {
      buttonPressed = true;
      pressStartTime = get_absolute_time();
    } else if (!currentButtonState && buttonPressed) {
      buttonPressed = false;
      uint64_t pressDuration =
        absolute_time_diff_us(pressStartTime, get_absolute_time()) / 1000;
      if (pressDuration >= longPressThreshold) {
        led.longPress();
        longPressed();
        isPressed = true;
      } else {
        led.shortPress();
        shortPressed();
        isPressed = true;
      }
    }
  }

  lastButtonState = currentButtonState;
  led.update();
  return isPressed;
}

void Button::longPressed() {
  uint8_t msg[2];
  msg[0] = 0xC0;
  msg[1] = longProgram;
  tud_midi_n_stream_write(0, 0, msg, 2);
  sendUartMsg(msg);
}

void Button::shortPressed() {
  uint8_t msg[2];
  msg[0] = 0xC0;
  msg[1] = shortProgram;
  tud_midi_n_stream_write(0, 0, msg, 2);
  sendUartMsg(msg);
}

void Button::sendUartMsg(uint8_t msg[2]) {
  uart_putc(uart0, msg[0]);
  uart_putc(uart0, msg[1]);
}

bool Button::updateCortex() {
  bool eventOccurred = false;
  const uint debounceDelay = 50;
  const uint longPressThreshold = 500;

  bool currentButtonState = gpio_get(pin);

  if (currentButtonState != lastButtonState) {
    lastDebounceTime = get_absolute_time();
  }

  if (absolute_time_diff_us(lastDebounceTime, get_absolute_time()) > debounceDelay * 1000) {
    if (currentButtonState && !buttonPressed) {
      buttonPressed = true;
      pressStartTime = get_absolute_time();
    } else if (!currentButtonState && buttonPressed) {
      buttonPressed = false;
      uint64_t pressDuration = absolute_time_diff_us(pressStartTime, get_absolute_time()) / 1000;
      if (pressDuration >= longPressThreshold) {
        led.setPins(0, 1);
        longPressed();
        eventOccurred = true;
      } else {
        led.setPins(1, 0);
        shortPressed();
        eventOccurred = true;
      }
    }
  }
  lastButtonState = currentButtonState;
  return eventOccurred;
}

bool Button::getPin() {
  return gpio_get(pin);
}