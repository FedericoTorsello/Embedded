#include "LedTask.h"

LedTask::LedTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void LedTask::init(int period) {
    Task::init(period);
    this->led = new Led(pin);
    led->switchOn();
}

void LedTask::tick() {
    if (pContext->isObjDetected()) {
        led->switchOn();
    } else {
        led->switchOff();
    }
}
