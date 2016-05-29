#include "LedTask.h"

LedTask::LedTask(int pin, Context* pContext) {
    this->pin = pin;
    this->led = new Led(pin);
    this->pContext = pContext;
}

void LedTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);

}

void LedTask::tick() {
    Task::callFoo();
    // if (pContext->isPadlockOpen()) {
    //     led->switchOn();
    // } else {
    //     led->switchOff();
    // }
}
