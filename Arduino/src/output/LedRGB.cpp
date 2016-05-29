#include "LedRGB.h"

LedRGB::LedRGB(int r, int g, int b) {
    red = new LedPwm(r, 0);
    green = new LedPwm(g, 0);
    blue = new LedPwm(b, 0);
}

void LedRGB::switchOff() {
    red->switchOff();
    green->switchOff();
    blue->switchOff();
}

void LedRGB::switchOn() {
    red->switchOn();
    green->switchOn();
    blue->switchOn();
}

void LedRGB::setColor(int r, int g, int b) {
    red->setIntensity(r);
    green->setIntensity(g);
    blue->setIntensity(b);
}
