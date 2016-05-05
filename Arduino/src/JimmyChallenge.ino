#include "Scheduler.h"
#include "ButtonTask.h"
#include "LedTask.h"
#include "SonarTask.h"
#include "GameTask.h"
#include "MsgService.h"

Scheduler sched;

void setup() {
    MsgService.init("OKKOKOKOK");
    sched.init(100);
    Context *c = new Context(0.5);

    SonarTask *t0 = new SonarTask(11, 12, c);
    t0->init(100);
    sched.addTask(t0);

    LedTask *t1 = new LedTask(13, c);
    t1->init(100);
    sched.addTask(t1);
}

void loop() {
    sched.schedule();
}
