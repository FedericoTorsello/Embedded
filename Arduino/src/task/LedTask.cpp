#include "LedTask.h"

LedTask::LedTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->led = new Led(pin);
}

void LedTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedTask::tick() {
    Task::callFoo();
}
