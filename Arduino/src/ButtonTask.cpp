#include "ButtonTask.h"

ButtonTask::ButtonTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void ButtonTask::init(int period) {
    Task::init(period);
    btn = new Button(pin);
}

void ButtonTask::tick() {
    pContext->setGame(btn->readBool());
}
