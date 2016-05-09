#include "Scheduler.h"

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    timer.setupPeriod(basePeriod);
    nTasks = 0;
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS - 1) {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
        return false;
    }
}

void Scheduler::schedule() {
    timer.waitForNextTick();
    for (Task *task : taskList) {
        if (task->updateAndCheckTime(basePeriod) && task->isEnabled()) {
            // cli();
            task->tick();
            // sei();
        }
    }
}
