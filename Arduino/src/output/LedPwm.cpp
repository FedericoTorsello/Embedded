#include "LedPwm.h"

LedPwm::LedPwm(int pin) : Led(pin) {
    currentIntensity = 128;
    isOn = false;
}

LedPwm::LedPwm(int pin, int intensity) : Led(pin) {
    isOn = false;
    currentIntensity = intensity;
}

void LedPwm::switchOn() {
    analogWrite(pin, currentIntensity);
    isOn = true;
}

void LedPwm::setIntensity(int value) {
    currentIntensity = value;
    if (isOn) {
        analogWrite(pin, currentIntensity);
    }
}

void LedPwm::switchOff() {
    analogWrite(pin, 0);
    isOn = false;
}
