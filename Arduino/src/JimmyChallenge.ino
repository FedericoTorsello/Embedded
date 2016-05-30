#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "output/LedRound.h"
#include "output/Multiplexer.h"
#include "task/SonarTask.h"
#include "task/LedTask.h"
#include "task/LedPwmTask.h"
#include "task/LedRoundTask.h"
#include "task/ButtonTask.h"
#include "task/BuzzerTask.h"

// configurazione porta seriale e messaggi
const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 100;
const int DEBOUNCE_DELAY = 40;
const String FROM_ARDUINO = "arduino";
const String TO_REMOTE = "remote";

// configurazione task
int channel[4] = {2, 3, 4, 5}; // pin che controllano i canali A,B,C,D del mux
const int BUZZER_PIN = 6;
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
// const int LED_RGB_R = 9;
// const int LED_RGB_G = 10;
// const int LED_RGB_B = 11;
const int BUTTON_PIN = 12;
const int LED_PIN_13 = 13;
const int LED_PWM = 5;

Context* pContext;
Scheduler sched;

SonarTask* t0;
ButtonTask* t1;
BuzzerTask* t2;
LedTask* t3;
LedPwmTask* t4;
LedRoundTask* t5;

void setup() {
    pContext = new Context(MAX_DISTANCE_SONAR);
    pContext->newRandomNumber();

    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    //** SonarTask
    t0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    t0->init(50,
             [] {
        int level = pContext->getLevelToPlay();
        int secretNum = pContext->getRandomNumber();
        switch (level) {
        case 0: playLevel(t0, level, 6, secretNum); break;
        case 1: playLevel(t0, level, 5, secretNum); break;
        case 2: playLevel(t0, level, 4, secretNum); break;
        case 3: playLevel(t0, level, 3, secretNum); break;
        default: {
            if(!pContext->isGameOver()) {
                msgService.sendMsg("Gioco Finito", FROM_ARDUINO, TO_REMOTE);
                pContext->setGameOver(true);
            }
        }
        }
    }
             );
    sched.addTask(t0);

    //** ButtonTask
    t1 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    t1->init(50, [] {
            pContext->setButtonPressed(t1->btn->readBool());
            if(t1->btn->readBool()){
            msgService.sendMsg("Button premuto", FROM_ARDUINO, TO_REMOTE);
            }
    });
    sched.addTask(t1);

    //** BuzzerTask
    t2 = new BuzzerTask(BUZZER_PIN, pContext);
    t2->init(50, [] {
        // sintassi: playSound(nSound)
        if(!pContext->isGameOver()) {
            if (pContext->isPadlockDetected()) {
                t2->buzzer->playSound(0);
            } else {
                t2->buzzer->playSound(1);
            }
        } else {}
    });
    sched.addTask(t2);

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

    //** LedPwmTask
    t4 = new LedPwmTask(LED_PWM, pContext);
    t4->init(50, [] {
        if (pContext->isPadlockDetected()) {
            t4->ledPwm->switchOn();
        } else {
            t4->ledPwm->switchOff();
        }
    });
    sched.addTask(t4);

    //** LedRoundTask
    t5 = new LedRoundTask(channel, 5, pContext);
    t5->init(50, [] {
        t5->led->carousel(50);
    });
    sched.addTask(t5);
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

    // print numero segreto da indovinare
    // msgService.sendMsg(String(numSegreto), FROM_ARDUINO, TO_REMOTE);

    // print distance
    // msgService.sendMsg(String(distance), FROM_ARDUINO, TO_REMOTE);

    if(distance <= numSegreto + delta && distance >= numSegreto - delta && !pContext->isPadlockOpen()) {
        pContext->setPadlockDetected(true);
        statoDiScasso = false;

        timer1 = millis()/1000;
        timer1 = timer1 - timer2;     // inizializzazione a zero

        if(tempoCorretto && timer1 == 0) {
            msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", FROM_ARDUINO, TO_REMOTE);
            pContext->setPadlockOpen(true);
            t0->tempoCorretto = false;
            pContext->setPadlockOpen(false);
            pContext->setLevelToPlay(currentLevel);
        }

        if(timer1 >= 0 && timer1 <= 1 && !statoDiScasso) {
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
            timer3 = timer3 - timer2 - 4;      // -4 per far partire il tempo t3 da zero

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
