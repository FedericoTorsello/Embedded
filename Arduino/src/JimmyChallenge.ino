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
const int DEBOUNCE_DELAY = 30; // un debounce delay a 30 sembra un buon compromesso
const int NUM_MUX_CHANNEL = 4;

// configurazione task
// pin digital write
const int BUTTON_PIN = 2;
int muxChannel[NUM_MUX_CHANNEL] = {4, 5, 12, 13}; // pin che controllano i canali A,B,C,D del mux
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;

// pin PWM 3, 5, 6, 9, 10, 11 (il pin 5 serve al mux)
const int BUZZER_PIN = 3;
const int LED_PWM = 6;
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
    msgService.init(BAUD, "JimmyChallenge");
    sched.init(100);

    const String FROM_ARDUINO = "arduino";
    const String TO_REMOTE = "remote";

    pContext = new Context(MAX_DISTANCE_SONAR, new Multiplexer(muxChannel, NUM_MUX_CHANNEL));
    pContext->newRandomNumber();
    pContext->setFrom(FROM_ARDUINO);
    pContext->setTo(TO_REMOTE);

    //** SonarTask
    sonarT0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    sonarT0->init(50, [] {
        if(!pContext->isGameOver()) {
            int level = pContext->getLevelToPlay();
            int secretNum = pContext->getRandomNumber();
            switch (level) {
            case 1: sonarT0->playLevel(level, 5, secretNum); break;
            // case 2: sonarT0->playLevel(level, 4, secretNum); break;
            // case 3: sonarT0->playLevel(level, 3, secretNum); break;
            // case 4: sonarT0->playLevel(level, 3, secretNum); break;
            // case 5: sonarT0->playLevel(level, 3, secretNum); break;
            // case 6: sonarT0->playLevel(level, 2, secretNum); break;
            default:
                msgService.sendMsg("Gioco Finito!!!", pContext->getFrom(), pContext->getTo());
                pContext->setGameOver(true);
                break;
            }
        } else {
            pContext->carousel();
        }
    });
    sched.addTask(sonarT0);

    //** ButtonTask
    buttonT0 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    buttonT0->init(50, [] {
        if(!pContext->isGameOver()) {
            bool buttonState = buttonT0->btn->readBool();
            pContext->setButtonPressed(buttonState);
            if(buttonState) {
                msgService.sendMsg("Secret number " + String(pContext->getRandomNumber()),
                                   pContext->getFrom(), pContext->getTo());
            }
        }
    });
    sched.addTask(buttonT0);

    //** BuzzerTask
    buzzerT0 = new BuzzerTask(BUZZER_PIN, pContext);
    buzzerT0->init(50, [] {
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
        if(!pContext->isGameOver()) {
            if (pContext->isPadlockDetected()) {
                ledT0->led->switchOn();
            } else {
                ledT0->led->switchOff();
            }
        }
    });
    sched.addTask(ledT0);

    //** LedPwmTask
    ledPwmT0 = new LedPwmTask(LED_PWM, pContext);
    ledPwmT0->init(50, [] {
        if (pContext->isGameOver()) {
            for (int i = 10; i < 255; i++) {
                ledPwmT0->ledPwm->setIntensity(i);
                ledPwmT0->ledPwm->switchOn();
                delay(3);
            }
            ledPwmT0->ledPwm->switchOff();
        }
    });
    sched.addTask(ledPwmT0);

    //** LedPwmTask
    ledRgbT0 = new LedRgbTask(LED_RGB_R, LED_RGB_G, LED_RGB_B, pContext);
    ledRgbT0->init(50, [] {
        if(!pContext->isGameOver()) {
            if (!pContext->isPadlockDetected()) {
                ledRgbT0->ledRgb->setColor(128, 255, 255);
            } else if (pContext->isStatoDiScasso()) {
                switch (pContext->getDangerLevel()) {
                case 0: ledRgbT0->ledRgb->setColor(0, 255, 0); break;                 // green = lucchetto aperto
                case 1: ledRgbT0->ledRgb->setColor(0, 0, 165); break;                 // blue = alert
                case 2: ledRgbT0->ledRgb->setColor(255, 255, 0); break;                 // yellow = lieve pericolo rottura
                case 3: ledRgbT0->ledRgb->setColor(255, 165, 0); break;                 // orange = forte pericolo rottura
                case 4: ledRgbT0->ledRgb->setColor(255, 0, 0); break;                 // red == lucchetto rotto
                default: ledRgbT0->ledRgb->setColor(128, 255, 255); break;
                }
            }
        }
    });
    sched.addTask(ledRgbT0);
}

void loop() {
    sched.schedule();
}
