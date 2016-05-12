#include "Scheduler.h"
#include "MessageService.h"
#include "SonarTask.h"
#include "LedTask.h"
#include "LedRound.h"

const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
int channel[] = { 2, 3, 4, 5 };
Scheduler sched;
Context *c = new Context(0.5);

void setup() {
    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);
}

void loop() {
    sched.schedule();
}
