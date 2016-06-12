#include "BuzzerTask.h"

/**@brief ###Init pin and context */
BuzzerTask::BuzzerTask(const int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
    this->buzzer = new Buzzer(this->pin);
}

/**@brief ###Set the period time for the task execution and the behaviour */
void BuzzerTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

/**@brief ### The function to execute when the scheduler gives the resources to the task */
void BuzzerTask::tick() {
    this->lambdaTick();
}
