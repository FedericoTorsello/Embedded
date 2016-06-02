#include "LedPwm.h"

LedPwm::LedPwm(int pin) : Led(pin) {
    currentIntensity = 128;
}

LedPwm::LedPwm(int pin, int intensity) : Led(pin) {
    currentIntensity = intensity;
}

void LedPwm::switchOn() {
    analogWrite(pin, currentIntensity);
}

void LedPwm::setIntensity(int value) {
    currentIntensity = value;
        analogWrite(pin, currentIntensity);
}

void LedPwm::switchOff() {
    analogWrite(pin, 0);
}
