#include "LedPwmTask.h"

LedPwmTask::LedPwmTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void LedPwmTask::init(int period) {
    Task::init(period);
    ledPwm = new LedPwm(pin);
    ledPwm->switchOn();
}

void LedPwmTask::tick() {
    if (pContext->isObjDetected()) {
        float d = pContext->getObjDistance();
        int val = (pContext->getMaxDistance() - d)*255;
        if (val >= 0 && val <= 255) {
            ledPwm->setIntensity(val);
        }
    } else {
        ledPwm->setIntensity(0);
    }
}
