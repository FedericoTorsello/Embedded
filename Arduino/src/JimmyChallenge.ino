#include "Scheduler.h"
#include "ButtonTask.h"
#include "LedTask.h"
#include "SonarTask.h"
#include "GameTask.h"
#include "MsgService.h"

Scheduler sched;

void setup() {

}

void loop() {
    sched.schedule();
}
