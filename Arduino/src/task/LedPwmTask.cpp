#include "LedPwmTask.h"

/**@brief ###Init pin and context */
LedPwmTask::LedPwmTask(const int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->ledPwm = new LedPwm(this->pin);
}

/**@brief ###Set the period time for the task execution and the behaviour */
void LedPwmTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

/**@brief ### The function to execute when the scheduler gives the resources to the task */
void LedPwmTask::tick() {
    this->lambdaTick();
}
