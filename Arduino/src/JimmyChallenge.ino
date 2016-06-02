#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "task/SonarTask.h"
#include "task/LedTask.h"
#include "task/LedPwmTask.h"
#include "task/LedRgbTask.h"
#include "task/ButtonTask.h"
#include "task/BuzzerTask.h"

// configurazione porta seriale e messaggi
const int BAUD = 9600;
const int MAX_DISTANCE_SONAR = 50;
const int DEBOUNCE_DELAY = 40;
const String FROM_ARDUINO = "arduino";
const String TO_REMOTE = "remote";
const int NUM_MUX_CHANNEL = 4;

// configurazione task
// pin digital write
int muxChannel[NUM_MUX_CHANNEL] = {4, 5, 12, 13}; // pin che controllano i canali A,B,C,D del mux
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
const int BUTTON_PIN = 2;

// pin PWM 3, 5, 6, 9, 10, 11 (il pin 5 serve al mux)
const int LED_PWM = 3;
const int BUZZER_PIN = 6;
const int LED_RGB_R = 9;
const int LED_RGB_G = 10;
const int LED_RGB_B = 11;

Context* pContext;
Scheduler sched;

// task
SonarTask* sonarT0;
ButtonTask* buttonT0;
BuzzerTask* buzzerT0;
LedTask* ledT0;
LedPwmTask* ledPwmT0;
LedRgbTask* ledRgbT0;

void setup() {
    pContext = new Context(MAX_DISTANCE_SONAR);
    pContext->newRandomNumber();

    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    //** SonarTask
    sonarT0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    sonarT0->init(50,
                  [] {
        int level = pContext->getLevelToPlay();
        int secretNum = pContext->getRandomNumber();
        switch (level) {
        case 0: playLevel(sonarT0, level, 6, secretNum); break;
        case 1: playLevel(sonarT0, level, 5, secretNum); break;
        case 2: playLevel(sonarT0, level, 4, secretNum); break;
        case 3: playLevel(sonarT0, level, 3, secretNum); break;
        default:
            if(!pContext->isGameOver()) {
                msgService.sendMsg("Gioco Finito", FROM_ARDUINO, TO_REMOTE);
                pContext->setGameOver(true);
            }
        }
    }
                  );
    sched.addTask(sonarT0);

    //** ButtonTask
    buttonT0 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    buttonT0->init(50, [] {
        bool buttonState = buttonT0->btn->readBool();
        pContext->setButtonPressed(buttonState);
        if(buttonState) {
            msgService.sendMsg("Secret number " + String(pContext->getRandomNumber()), FROM_ARDUINO, TO_REMOTE);
        }
    });
    sched.addTask(buttonT0);

    //** BuzzerTask
    buzzerT0 = new BuzzerTask(BUZZER_PIN, pContext);
    buzzerT0->init(50, [] {
        // sintassi: playSound(nSound)
        if(!pContext->isGameOver()) {
            if (pContext->isPadlockDetected()) {
                buzzerT0->buzzer->playSound(0);
            } else {
                buzzerT0->buzzer->playSound(1);
            }
        }
    });
    sched.addTask(buzzerT0);

    //** LedTask
    ledT0 = new LedTask(LED_PWM, pContext);
    ledT0->init(50, [] {
        if (pContext->isPadlockDetected()) {
            ledT0->led->switchOn();
        } else {
            ledT0->led->switchOff();
        }
    });
    sched.addTask(ledT0);

    //** LedPwmTask
    // ledPwmT0 = new LedPwmTask(LED_PWM, pContext);
    // ledPwmT0->init(50, [] {
    //     if (pContext->isPadlockDetected()) {
    //         ledPwmT0->ledPwm->switchOn();
    //     } else {
    //         ledPwmT0->ledPwm->switchOff();
    //     }
    // });
    // sched.addTask(ledPwmT0);

    //** LedPwmTask
    ledRgbT0 = new LedRgbTask(LED_RGB_R, LED_RGB_G, LED_RGB_B, pContext);
    ledRgbT0->init(50, [] {
        if (pContext->isPadlockDetected()) {
            ledRgbT0->ledRgb->setColor(128, 255, 255);
        } else {
            ledRgbT0->ledRgb->setColor(255, 255, 128);
        }
    });
    sched.addTask(ledRgbT0);
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
    // msgService.sendMsg("Secret number " + String(numSegreto), FROM_ARDUINO, TO_REMOTE);

    // print distance
    // msgService.sendMsg("Distance " + String(distance), FROM_ARDUINO, TO_REMOTE);

    if(distance <= numSegreto + delta && distance >= numSegreto - delta && !pContext->isPadlockOpen()) {
        pContext->setPadlockDetected(true);
        statoDiScasso = false;

        timer1 = millis()/1000;
        timer1 = timer1 - timer2;     // inizializzazione a zero

        // girare la chia
        if(tempoCorretto && timer1 == 0) {
            msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", FROM_ARDUINO, TO_REMOTE);
            sonarTask->tempoCorretto = false;
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
            timer3 = timer3 - timer2 - 4;      // -4 per far partire il tempo ledT0 da zero

            switch (timer3) {
            case 1: msgService.sendMsg("Stai scassinando il lucchetto", FROM_ARDUINO, TO_REMOTE); break;
            case 2: msgService.sendMsg("Ancora un po' di pazienza", FROM_ARDUINO, TO_REMOTE); break;
            case 3: msgService.sendMsg("Livello " + String(currentLevel) + " passato :D", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true; break;
            case 4: msgService.sendMsg("...però non restare fermo...", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true; break;
            case 5: msgService.sendMsg("...stai rishiando la rottura...", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true; break;
            case 6: msgService.sendMsg("Attento! Lo rompi davvero!", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = true; break;
            case 7: msgService.sendMsg("Nooo, l'hai rotto! Devi riprovare", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = false;
                pContext->setPadlockOpen(false); break;
            default: msgService.sendMsg("Devi ricominciare!", FROM_ARDUINO, TO_REMOTE); break;
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
