#include "BuzzerTask.h"

BuzzerTask::BuzzerTask(int pin, Context* pContext) {
    this->pin = pin;
    this->pContext = pContext;
}

void BuzzerTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
    this->buzzer = new Buzzer(pin);
}

void BuzzerTask::tick() {
    Task::callFoo();
    // int varDelayValue;
    // int varNumCycles;
    //
    // if(varDelayValue == 0){
    //     varDelayValue = 1;
    // }
    // if(varNumCycles == 0){
    //     varNumCycles = 1;
    // }
    //
    // buzzer->playSound(1, varDelayValue, varNumCycles);
}
