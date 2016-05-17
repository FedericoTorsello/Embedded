#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "output/LedRound.h"
#include "output/Multiplexer.h"
#include "tasks/SonarTask.h"
#include "tasks/LedTask.h"
#include "tasks/ButtonTask.h"

const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 100;

// pin che controllano i canali A,B,C,D del mux
// int channel[5] = {2,3,4,5,6};
Scheduler sched;
Context *c = new Context(0.5);

void setup() {
  msgService.init(BAUD, "JimmyChallenge");
  sched.init(100);

  Task* t0 = new ButtonTask(2, 40, c);
  t0->init(50);
  sched.addTask(t0);
}

void loop() {
  sched.schedule();
}
