#include "BuzzerTask.h"

BuzzerTask::BuzzerTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->buzzer = new Buzzer(pin);
}

void BuzzerTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void BuzzerTask::tick() {
    Task::callFoo();
}
