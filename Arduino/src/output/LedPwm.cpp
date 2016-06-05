#include "LedPwm.h"

LedPwm::LedPwm(const int pin) : Led(pin) {
    currentIntensity = 0;
}

// costruttore per gestire i led RGB
LedPwm::LedPwm(int pin, int intensity) : Led(pin) {
    currentIntensity = intensity;
}

void LedPwm::switchOn() {
    analogWrite(pin, currentIntensity);
}

void LedPwm::switchOff() {
    analogWrite(pin, 0);
}

void LedPwm::setIntensity(int value) {
    currentIntensity = value;
    analogWrite(pin, currentIntensity);
}
