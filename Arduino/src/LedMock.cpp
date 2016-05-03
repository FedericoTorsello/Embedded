#include "LedMock.h"

LedMock::LedMock(int pin) {
    this->pin = pin;
}

void LedMock::switchOn() {
    printf("LED %i HIGH", this->pin);
}

void LedMock::switchOff() {
    printf("LED %i LOW", this->pin);
};
