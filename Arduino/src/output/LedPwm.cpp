#include "LedPwm.h"

/** @brief ###Config the led's pin */
LedPwm::LedPwm(const int pin) : Led(pin) {
    switchOff();
}

/** @brief ###Config the led's pin and init the intensity of the led */
LedPwm::LedPwm(const int pin, const int intensity) : Led(pin) {
    switchOff();
}

/** @brief ###Turn the led on */
void LedPwm::switchOn() {
    analogWrite(pin, 255);
}

/** @brief ###Turn the led off */
void LedPwm::switchOff() {
    analogWrite(pin, 0);
}

/** @brief ###Set the intensity of the pwm led */
void LedPwm::setIntensity(const uint8_t value) {
    analogWrite(pin, value);
}
