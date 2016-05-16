#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "tasks/SonarTask.h"
#include "output/LedRound.h"
#include "tasks/LedTask.h"
#include "tasks/ButtonTask.h"

const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
int channel[] = { 2, 3, 4, 5 };
Scheduler sched;
Context *c = new Context(0.5);

int trigPin = 11;
int echoPin = 12;
int MAX_DISTANCE = 100;

void setup() {
    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    Task* t0 = new SonarTask(trigPin,echoPin, MAX_DISTANCE, c);
    t0->init(100);
    sched.addTask(t0);

    // Task* t1 = new LedTask(13,c);
    // t1->init(100);
    // sched.addTask(t1);
}

void loop() {
    sched.schedule();
}
