#include "LedRgbTask.h"

/**@brief ###Init pins and context */
LedRgbTask::LedRgbTask(const int pin1, const int pin2, const int pin3, Context* pContext) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pContext = pContext;
    this->ledRgb = new LedRgb(this->pin1, this->pin2, this->pin3);
}

/**@brief ###Set the period time for the task execution and the behaviour */
void LedRgbTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

/**@brief ### The function to execute when the scheduler gives the resources to the task */
void LedRgbTask::tick() {
    this->lambdaTick();
}
