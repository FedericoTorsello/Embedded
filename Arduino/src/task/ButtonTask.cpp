#include "ButtonTask.h"

/**@brief ###Init pin, debounce time and context */
ButtonTask::ButtonTask(const int pin,  const unsigned long debounceDelay, Context* pContext) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    this->pContext = pContext;
    this->btn = new Button(this->pin, this->debounceDelay);
}

/**@brief ###Set the period time for the task execution and the behaviour */
void ButtonTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

/**@brief ### The function to execute when the scheduler gives the resources to the task */
void ButtonTask::tick() {
    this->lambdaTick();
}
