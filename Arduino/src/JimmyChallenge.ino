#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "output/LedRound.h"
#include "output/Multiplexer.h"
#include "tasks/SonarTask.h"
#include "tasks/LedTask.h"
#include "tasks/ButtonTask.h"
#include "tasks/BuzzerTask.h"

// configurazione porta seriale e messaggi
const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
const int DEBOUNCE_DELAY = 40;
const String FROM_ARDUINO = "arduino";
const String TO_REMOTE = "remote";

// configurazione task
const int BUTTON_PIN = 2;
const int BUZZER_PIN = 3;
// pin che controllano i canali A,B,C,D del mux
// int channel[5] = {4,5,6,7,8};
const int TRIG_PIN = 11;
const int ECHO_PIN = 12;
const int LED_PIN_13 = 13;

// int distance = 0;

Context* pContext;
Scheduler sched;

SonarTask* t0;
ButtonTask* t1;
BuzzerTask* t2;
LedTask* t3;

void setup() {
    pContext = new Context(MAX_DISTANCE_SONAR);

    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    //** SonarTask
    t0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    t0->init(50,
             [] {
        switch (pContext->getLevelToPlay()) {
        case 0: playLevel(t0, 0, 4, 20); break;
        case 1: playLevel(t0, 1, 4, 30); break;
        case 2: playLevel(t0, 2, 4, 40); break;
        case 3: playLevel(t0, 3, 4, 20); break;
        default: break;
        }
    }
             );
    sched.addTask(t0);

    //** ButtonTask
    t1 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    t1->init(50, [] {
        pContext->setButtonPressed(t1->btn->readBool());
    });
    sched.addTask(t1);

    // **BuzzerTask
    // t2 = new BuzzerTask(BUZZER_PIN, pContext);
    // t2->init(50, [] {
    //     // sintassi: playSound(nSong ,DelayValue, NumCycles)
    //     t2->buzzer->playSound(1, 2, 4);
    // });
    // sched.addTask(t2);

    //** LedTask
    t3 = new LedTask(LED_PIN_13, pContext);
    t3->init(50, [] {
        if (pContext->isPadlockDetected()) {
            t3->led->switchOn();
        } else {
            t3->led->switchOff();
        }
    });
    sched.addTask(t3);
}

void loop() {
    sched.schedule();
}

void playLevel(SonarTask* sonarTask, int currentLevel, int delta, int numSegreto){

    // gestire i tempi
    unsigned long &timer1 = sonarTask->timer1;
    unsigned long &timer2 = sonarTask->timer2;
    unsigned long &timer3 = sonarTask->timer3;
    bool &tempoCorretto = sonarTask->tempoCorretto;

    bool statoDiScasso = false;

    int distance = sonarTask->sonar->readDistance();
    pContext->setCurrentDistance(distance);

    // print distance
    // msgService.sendMsg(String(distance), FROM_ARDUINO, TO_REMOTE);

    if(distance <= numSegreto + delta && distance >= numSegreto - delta && !pContext->isPadlockOpen()) {
        pContext->setPadlockDetected(true);
        statoDiScasso = false;

        timer1 = millis()/1000;
        timer1 = timer1 - timer2; // inizializzazione a zero

        if(tempoCorretto && timer1 == 0) {
            msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", FROM_ARDUINO, TO_REMOTE);
            pContext->setPadlockOpen(true);
            sonarTask->tempoCorretto = false;
            pContext->setPadlockOpen(false);
            pContext->setLevelToPlay(currentLevel);
        }

        if(timer1 == 1 && !statoDiScasso) {
            msgService.sendMsg("Hai trovato il lucchetto", FROM_ARDUINO, TO_REMOTE);
        } else if(timer1 == 2) {
            msgService.sendMsg("Bene, stai calmo", FROM_ARDUINO, TO_REMOTE);
        } else if (timer1 == 3 || timer1 == 4) {
            msgService.sendMsg("Bisogna stare attenti...", FROM_ARDUINO, TO_REMOTE);
        } else if (timer1 > 4) {
            statoDiScasso = true;
        }

        if(statoDiScasso) {
            timer3 = millis()/1000;
            timer3 = timer3 - timer2 - 4;  // -4 per far partire il tempo t3 da zero

            if(timer3 == 1) {
                msgService.sendMsg("Stai scassinando il lucchetto", FROM_ARDUINO, TO_REMOTE);
            } else if (timer3 == 2) {
                msgService.sendMsg("Ancora un po' di pazienza", FROM_ARDUINO, TO_REMOTE);
            } else if (timer3 == 3) {
                msgService.sendMsg("Livello " + String(currentLevel) + " passato :D", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true;
            } else if (timer3 == 4) {
                msgService.sendMsg("...però non restare fermo...", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true;
            } else if (timer3 == 5) {
                msgService.sendMsg("...stai rishiando la rottura...", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true;
            } else if (timer3 == 6) {
                msgService.sendMsg("Attento! Lo rompi davvero!", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true;
            } else if (timer3 == 7) {
                msgService.sendMsg("Nooo, l'hai rotto! Devi riprovare", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = false;
                pContext->setPadlockOpen(false);
            }
        }
    } else {
        if(!pContext->isPadlockOpen()) {
            timer2 = millis()/1000;
            // msgService.sendMsg("NON APERTO", FROM_ARDUINO, TO_REMOTE);
            pContext->setPadlockOpen(false);
            pContext->setPadlockDetected(false);
        }
    }
}
