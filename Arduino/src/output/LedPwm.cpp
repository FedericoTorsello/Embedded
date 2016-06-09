#include "LedPwm.h"

LedPwm::LedPwm(const int pin) : Led(pin) {
    switchOff();
}

// costruttore per gestire i led RGB
LedPwm::LedPwm(int pin, int intensity) : Led(pin) {

    switchOff();
}

void LedPwm::switchOn() {
    analogWrite(pin, 255);
}

void LedPwm::switchOff() {
    analogWrite(pin, 0);
}

void LedPwm::setIntensity(int value) {
    analogWrite(pin, value);
}
