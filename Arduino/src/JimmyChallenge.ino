#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "output/LedRound.h"
#include "output/Multiplexer.h"
#include "tasks/SonarTask.h"
#include "tasks/LedTask.h"
#include "tasks/ButtonTask.h"
#include "tasks/BuzzerTask.h"

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 3;
// pin che controllano i canali A,B,C,D del mux
// int channel[5] = {4,5,6,7,8};
const int TRIG_PIN = 11;
const int ECHO_PIN = 12;

const int LED_PIN = 13;

const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
const int DEBOUNCE_DELAY = 40;

Scheduler sched;
Context *c = new Context(MAX_DISTANCE_SONAR);

LedTask* t4;

void setup() {
    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    // Task* t0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, c);
    // t0->init(50);
    // sched.addTask(t0);

    // Task* t1 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, c);
    // t0->init(50);
    // sched.addTask(t1);
    //
    // Task* t2 = new BuzzerTask(BUZZER_PIN, c);
    // t2->init(50);
    // sched.addTask(t2);

    t4 = new LedTask(LED_PIN, c);
    t4->init(50, [] {
        Serial.println("OK");
    });
    sched.addTask(t4);
}

void loop() {
    sched.schedule();
}
