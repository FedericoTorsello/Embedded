#include "LedRoundTask.h"

LedRoundTask::LedRoundTask(int *pins, int size, Context* pContext) {
    this->pins = pins;
    this->size = size;
    this->pContext = pContext;
    led = new Multiplexer(pins, size);
}

void LedRoundTask::init(int period) {
    Task::init(period);
}

void LedRoundTask::tick() {
    led->carousel(300);
}
