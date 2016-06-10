#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "../task/Task.h"
#include "Timer.h"

class Scheduler {
private:
    const static int MAX_TASKS = 10;
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
