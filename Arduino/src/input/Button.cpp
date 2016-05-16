#include "Button.h"

Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin,INPUT);
}

bool Button::readBool() {
    return digitalRead(pin);
}
