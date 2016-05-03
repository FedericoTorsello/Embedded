#include "LedTask.h"

LedTask::LedTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void LedTask::init(int period) {
    Task::init(period);
    led = new LedPwm(pin);
    led->switchOn();
}

void LedTask::tick() {
    if (pContext->isObjDetected()) {
        float d = pContext->getObjDistance();
        int val = (pContext->getMaxDistance() - d)*255;
        if (val >= 0 && val <= 255) {
            led->setIntensity(val);
        }
    } else {
        led->setIntensity(0);
    }
}
