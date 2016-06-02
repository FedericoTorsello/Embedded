#include "LedPwmTask.h"

LedPwmTask::LedPwmTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->ledPwm = new LedPwm(pin);
}

void LedPwmTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedPwmTask::tick() {
    Task::callFoo();
    // if (pContext->isPadlockDetected()) {
    //     int d = pContext->getCurrentDistance();
    //     int val = (pContext->getMaxDistance() - d)*255;
    //     if (val >= 0 && val <= 255) {
    //         ledPwm->setIntensity(val);
    //     }
    // } else {
    //     ledPwm->setIntensity(0);
    // }
}