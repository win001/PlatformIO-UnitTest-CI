#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <Arduino.h>

class GPIOHandler {
public:
    GPIOHandler(uint8_t pin);
    bool initializeOutput();
    bool initializeInput();
    bool digitalWrite(bool state);
    int digitalRead();
    
private:
    uint8_t _pin;
};

#endif