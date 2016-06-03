#include "ButtonTask.h"

ButtonTask::ButtonTask(int pin,  int debounceDelay, Context* pContext) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    this->pContext = pContext;
    this->btn = new Button(pin, debounceDelay);
}

void ButtonTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);

}

void ButtonTask::tick() {
    Task::callFoo();
}
