#include "LedRoundTask.h"

LedRoundTask::LedRoundTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void LedRoundTask::init(int period) {
    Task::init(period);
    led = new LedRound(pin);
    led->switchOn();
}

void LedRoundTask::tick() {
    // if (pContext->isObjDetected()) {
        led->switchOn();
    // } else {
    //     led->switchOff();
    // }
}
