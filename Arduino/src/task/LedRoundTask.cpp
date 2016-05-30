#include "LedRoundTask.h"

LedRoundTask::LedRoundTask(int *pins, int size, Context* pContext) {
    this->pins = pins;
    this->size = size;
    this->pContext = pContext;
    this->led = new Multiplexer(pins, size, false);
    // this->led = new LedRound(pins, size);
}

void LedRoundTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedRoundTask::tick() {
    Task::callFoo();
    // led->carousel(300);
}
