#include "Led.h"

/** @brief ###Config the led's pin */
Led::Led(const int pin) {
    this->pin = pin;
    pinMode(pin,OUTPUT);
}

/** @brief ###Turn the led on */
void Led::switchOn() {
    digitalWrite(pin,HIGH);
}

/** @brief ###Turn the led off */
void Led::switchOff() {
    digitalWrite(pin,LOW);
}
