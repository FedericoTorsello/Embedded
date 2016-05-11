#include "Scheduler.h"
#include "SonarTask.h"
#include "MsgService.h"
#include "LedTask.h"
#include "LedRoundTask.h"

const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
int channel[] = { 2, 3, 4, 5 };
Scheduler sched;

void setup() {
    MsgService.init(BAUD, "JimmyChallenge");
    sched.init(100);
    Context *c = new Context(0.5);

    SonarTask *t0 = new SonarTask(12, 11, MAX_DISTANCE_SONAR, c);
    t0->init(100);
    sched.addTask(t0);

    LedTask *t1 = new LedTask(13, c);
    t1->init(10);
    sched.addTask(t1);

    LedRoundTask *t2 = new LedRoundTask(channel, 4, c);
    t2->init(10);
    sched.addTask(t2);
}

void loop() {
    sched.schedule();
}
