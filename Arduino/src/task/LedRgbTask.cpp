#include "LedRgbTask.h"

LedRgbTask::LedRgbTask(int pin1, int pin2, int pin3, Context* pContext) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pContext = pContext;
    this->ledRgb = new LedRgb(pin1, pin2, pin3);
}

void LedRgbTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedRgbTask::tick() {
    Task::callFoo();
}
