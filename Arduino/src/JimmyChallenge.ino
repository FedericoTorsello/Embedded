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

Context *pContext = new Context(MAX_DISTANCE_SONAR);

SonarTask* t0;
ButtonTask* t1;
BuzzerTask* t2;
LedTask* t3;

Scheduler sched;

void setup() {
    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    t0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    t0->init(50,
             [] {
        if(pContext->getLevelToPlay() == 0){
            playLevel(t0, 0, 4, 20);
        }
        if(pContext->getLevelToPlay() == 1) {
            playLevel(t0, 1, 4, 30);
        }
    }
             );
    sched.addTask(t0);

    t1 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    t1->init(50, [] {
        pContext->setButtonPressed(t1->btn->readBool());
    });
    sched.addTask(t1);

    t2 = new BuzzerTask(BUZZER_PIN, pContext);
    t2->init(50, [] {
        // int varDelayValue;
        // int varNumCycles;
        //
        // if(varDelayValue == 0){
        //     varDelayValue = 1;
        // }
        // if(varNumCycles == 0){
        //     varNumCycles = 1;
        // }
        //
        // t2->buzzer->playSound(1, varDelayValue, varNumCycles);
    });
    sched.addTask(t2);

    t3 = new LedTask(LED_PIN, pContext);
    t3->init(50, [] {
        if (pContext->isPadlockOpen()) {
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

void playLevel(SonarTask* t0, int currentLevel, int delta, int indovina){
    int &timer1 = t0->timer1;
    int &timer2= t0->timer2;
    int &timer3 = t0->timer3;
    bool &tempoCorretto = t0->tempoCorretto;
    int distance = t0->sonar->readDistance();

    pContext->setCurrentDistance(distance);

    // print distance
    msgService.sendMsg(String(distance), "arduino", "remote");

    if(distance <= indovina + delta && distance >= indovina - delta && !pContext->isPadlockOpen()) {

        pContext->setPadlockDetected(true);

        timer1 = millis()/1000;
        timer1 = timer1 - timer2;         // inizializzazione a zero

        if(tempoCorretto && timer1 == 0) {
            msgService.sendMsg("APERTO", "arduino", "remote");
            pContext->setLevelPassed(currentLevel);
            pContext->setPadlockOpen(true);
            pContext->setPadlockOpen(false);
            tempoCorretto = false;
        }

        switch (timer1) {
        case 1:
            Serial.println("hai trovato il lucchetto");
            break;

        case 2:
            Serial.println("ti stai avvicinando");
            break;

        case 3:
            Serial.println("ora bisogna stare attenti");
            break;

        case 4:
            Serial.println("ora bisogna stare attenti");
            break;
        }

        if (timer1 >= 4) {
            timer3 = millis()/1000;
            timer3 = timer3 - timer2 - 4;             // -4 per far partire il tempo t3 da zero

            switch (timer3) {
            case 1:
                Serial.println("stai scassinando il lucchetto");
                break;

            case 2:
                Serial.println("ancora un po' di pazienza");
                break;

            case 3:
                Serial.println("ce l'hai fatta!!! :D");
                tempoCorretto = true;
                break;
            }

            if(timer3 >= 4 && timer3 <= 5) {
                Serial.println("...però non restare fermo...");
                tempoCorretto = true;
            }

            if(timer3 == 6) {
                Serial.println("Attento! rischi di romperlo!");
                tempoCorretto = true;
            }

            if(timer3 >= 7) {
                Serial.println("Noooooo, l'hai rotto! Devi riprovare");
                tempoCorretto = false;
            }
        }
    }else{
        if(!pContext->isPadlockOpen()) {
            timer2 = millis()/1000;
            // msgService.sendMsg("NON APERTO", "arduino", "remote");
            pContext->setPadlockOpen(false);
            pContext->setPadlockDetected(false);
        }
    }
}
