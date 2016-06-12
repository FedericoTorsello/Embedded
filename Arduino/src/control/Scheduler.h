#ifndef __SCHEDULER__int
#define __SCHEDULER__

#include "../task/Task.h"
#include "Timer.h"

/** Run with round robin scheduling all tasks */
class Scheduler {
private:
    const static uint8_t MAX_TASKS = 10;
    int basePeriod;
    int nTasks;
    Task *taskList[MAX_TASKS];
    Timer timer;
public:
    void init(int);
    virtual bool addTask(Task *);
    virtual void schedule();
};

#endif
