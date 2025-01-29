#include "gpio_handler.h"
#include <Arduino.h>

GPIOHandler::GPIOHandler(uint8_t pin) : _pin(pin) {}

bool GPIOHandler::initializeOutput() {
    pinMode(_pin, OUTPUT);
    return true;
}

bool GPIOHandler::initializeInput() {
    pinMode(_pin, INPUT);
    return true;
}

bool GPIOHandler::digitalWrite(bool state) {
    ::digitalWrite(_pin, state ? HIGH : LOW);
    return true;
}

int GPIOHandler::digitalRead() {
    return ::digitalRead(_pin);
}