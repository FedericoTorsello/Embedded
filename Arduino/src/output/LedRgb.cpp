#include "LedRgb.h"

LedRgb::LedRgb(int r, int g, int b) {
    red = new LedPwm(r, 0);
    green = new LedPwm(g, 0);
    blue = new LedPwm(b, 0);
}

void LedRgb::switchOff() {
    red->switchOff();
    green->switchOff();
    blue->switchOff();
}

void LedRgb::switchOn() {
    red->switchOn();
    green->switchOn();
    blue->switchOn();
}

void LedRgb::setColor(int r, int g, int b) {
    red->setIntensity(r);
    green->setIntensity(g);
    blue->setIntensity(b);
}
