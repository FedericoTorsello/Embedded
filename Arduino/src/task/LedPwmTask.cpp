#include "LedPwmTask.h"

LedPwmTask::LedPwmTask(const int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->ledPwm = new LedPwm(this->pin);
}

void LedPwmTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedPwmTask::tick() {
    Task::callTick();
}
