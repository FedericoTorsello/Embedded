#include "ButtonTask.h"

ButtonTask::ButtonTask(int pin,  unsigned long debounceDelay, Context* pContext) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    this->pContext = pContext;
}

void ButtonTask::init(int period) {
    Task::init(period);
    btn = new Button(pin, debounceDelay);
}

void ButtonTask::tick() {
    btn->readBool();
    // Serial.println(state);
}
