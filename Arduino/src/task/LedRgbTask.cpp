#include "LedRgbTask.h"

LedRgbTask::LedRgbTask(const int pin1, const int pin2, const int pin3, Context* pContext) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pContext = pContext;
    this->ledRgb = new LedRgb(this->pin1, this->pin2, this->pin3);
}

void LedRgbTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void LedRgbTask::tick() {
    Task::callTick();
}
