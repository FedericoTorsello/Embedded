#include "LedRound.h"

LedRound::LedRound(int *p, int n) {
    pins = p;
    size = n;
    for (int pin = 0; pin < size; pin++) {
        pinMode(pins[pin], OUTPUT);
    }
}

void LedRound::switchOn() {
    for (int i = 0; i < size; ++i) {
        digitalWrite(pins[i], HIGH);
    }
}

void LedRound::switchRoundOn(int *who, int n) {
    if(n < size || n > 0 ){
        for (int i = 0; i < n; ++i) {
            digitalWrite(who[i], HIGH);
        }
    }
}

void LedRound::switchRoundOff(int *who, int n) {
    if(n < size || n > 0 ){
        for (int i = 0; i < n; ++i) {
            digitalWrite(pins[who[i]], LOW);
        }
    }
}

void LedRound::switchOff() {
    for (int i = 0; i < size; ++i) {
        digitalWrite(pins[i], LOW);
    }
}
