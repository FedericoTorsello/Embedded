#include "LedRoundTask.h"

LedRoundTask::LedRoundTask(int *pins, int size, Context* pContext) {
    this->pins = pins;
    this->size = size;
    this->pContext = pContext;
    this->led = new Multiplexer(pins, size, false);
}

void LedRoundTask::init(int period) {
    Task::init(period);
}

void LedRoundTask::tick(void (*f)()) {
    led->carousel(300);
}
