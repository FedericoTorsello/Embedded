#include "LedRgb.h"
/** @brief ###Config the led's pin */
LedRgb::LedRgb(const int r, const int g, const int b) {
    red = new LedPwm(r, 0);
    green = new LedPwm(g, 0);
    blue = new LedPwm(b, 0);
}

/** @brief ###Turn the led off */
void LedRgb::switchOff() {
    red->switchOff();
    green->switchOff();
    blue->switchOff();
}

/** @brief ###Turn the led on */
void LedRgb::switchOn() {
    red->switchOn();
    green->switchOn();
    blue->switchOn();
}

/** @brief ###Set the color of the RGB led with a (red, green, blue) value*/
void LedRgb::setColor(int r, int g, int b) {
    red->setIntensity(r);
    green->setIntensity(g);
    blue->setIntensity(b);
}
