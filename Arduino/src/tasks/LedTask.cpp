#include "LedTask.h"

LedTask::LedTask(int pin, Context* pContext) {
    this->pin = pin;
    this->led = new Led(pin);
    this->pContext = pContext;
}

void LedTask::init(int period) {
    Task::init(period);

}

void LedTask::tick(void (*f)()) {
    f();
    // if (pContext->isPadlockOpen()) {
    //     led->switchOn();
    // } else {
    //     led->switchOff();
    // }
}
