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
    pContext = new Context(MAX_DISTANCE_SONAR, new Multiplexer(muxChannel, NUM_MUX_CHANNEL));
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
        case 1: sonarT0->playLevel(level, 5, secretNum); break;
        case 2: sonarT0->playLevel(level, 4, secretNum); break;
        case 3: sonarT0->playLevel(level, 3, secretNum); break;
        case 4: sonarT0->playLevel(level, 3, secretNum); break;
        // case 5: sonarT0->playLevel(level, 3, secretNum); break;
        // case 6: sonarT0->playLevel(level, 2, secretNum); break;
        default:
            if(!pContext->isGameOver()) {
                msgService.sendMsg("Gioco Finito!!!", FROM_ARDUINO, TO_REMOTE);
            }
            pContext->setGameOver(true);
            break;
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
