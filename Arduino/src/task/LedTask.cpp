#include "LedTask.h"

/**@brief ###Init pin and context */
LedTask::LedTask(const int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->led = new Led(this->pin);
}

/**@brief ###Set the period time for the task execution and the behaviour */
void LedTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

/**@brief ### The function to execute when the scheduler gives the resources to the task */
void LedTask::tick() {
    this->lambdaTick();
}
