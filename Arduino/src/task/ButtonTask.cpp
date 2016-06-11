#include "ButtonTask.h"

ButtonTask::ButtonTask(const int pin,  const unsigned long debounceDelay, Context* pContext) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    this->pContext = pContext;
    this->btn = new Button(this->pin, this->debounceDelay);
}

void ButtonTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void ButtonTask::tick() {
    Task::callTick();
}
