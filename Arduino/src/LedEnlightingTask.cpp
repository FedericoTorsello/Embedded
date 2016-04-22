#include "LedEnlightingTask.h"
#include "Arduino.h"

LedEnlightingTask::LedEnlightingTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void LedEnlightingTask::init(int period) {
    Task::init(period);
    led = new LedPwm(pin);
    led->switchOn();
}

void LedEnlightingTask::tick() {
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
