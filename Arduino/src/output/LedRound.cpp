#include "LedRound.h"

LedRound::LedRound(int *p, int n) {
    pins = p;
    size = n;
    leds[n];
    for (int i = 0; i < size; i++) {
        pinMode(pins[i], OUTPUT);
        leds[n] = Led(pins[i]);
    }
}

void LedRound::switchOn() {
    for (int i = 0; i < size; ++i) {
        leds[i].switchOn();
    }
}

void LedRound::switchOff() {
    for (int i = 0; i < size; ++i) {
        leds[i].switchOff();
    }
}

void LedRound::switchOn(int *who, int n) {
    if(n < size || n > 0) {
        for (int i = 0; i < n; ++i) {
            leds[who[i]].switchOn();
        }
    }
}

void LedRound::switchOff(int *who, int n) {
    if(n < size || n > 0) {
        for (int i = 0; i < n; ++i) {
            leds[who[i]].switchOff();
        }
    }
}
