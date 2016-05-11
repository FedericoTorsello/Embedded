#include "LedRound.h"

LedRound::LedRound(int *pins, int size) {
    pins = pins;
    size = size;
    for (int pin = 0; pin < size; pin++) {
        pinMode(pins[pin], OUTPUT);
    }
}

void LedRound::switchOn() {
    for (int i = 0; i < size; i++) {
        digitalWrite(i, HIGH);
    }
}

void LedRound::switchRoundOn(int *who, int size) {
    for (int i = 0; i < size; i++) {
        digitalWrite(pins[who[i]], HIGH);
    }
}

void LedRound::switchRoundOff(int *who, int size) {
    for (int i = 0; i < size; i++) {
        digitalWrite(pins[who[i]], LOW);
    }
}

void LedRound::switchOff() {
    for (int i = 0; i < size; i++) {
        digitalWrite(i, LOW);
    }
}
