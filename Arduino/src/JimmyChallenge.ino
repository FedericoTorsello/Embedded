#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "task/SonarTask.h"
#include "task/LedTask.h"
#include "task/LedPwmTask.h"
#include "task/LedRgbTask.h"
#include "task/ButtonTask.h"
#include "task/BuzzerTask.h"

const int BAUD = 9600;                              /**< Serial baud rate */
const int MAX_DISTANCE_SONAR = 50;                  /**< Maximum distance game */
const int DEBOUNCE_DELAY = 30;                      /**< Button debounce delay */
const int NUM_MUX_CHANNEL = 4;                      /**< Number of input channels for the multiplexer */

// configurazione task
// pin digital write
const int BUTTON_PIN = 2;                           /**< Input digital from button */
int muxChannel[NUM_MUX_CHANNEL] = {4, 5, 12, 13};   /**< Input channels for the multiplexer */
const int TRIG_PIN = 7;                             /**< Trigger pin of sonar */
const int ECHO_PIN = 8;                             /**< Echo pin of sonar*/

// pin PWM 3, 5, 6, 9, 10, 11 (il pin 5 serve al mux)
const int BUZZER_PIN = 3;                           /**< Input pin for buzzer */
const int LED_PWM = 6;                              /**< Input pwm for led */
const int LED_RGB_R = 9;                            /**< Input pwm for color red of RGB led */
const int LED_RGB_G = 10;                           /**< Input pwm for color green of RGB led */
const int LED_RGB_B = 11;                           /**< Input pwm for color blue of RGB led */

Context* pContext;                                  /**< Context instance */
Scheduler sched;                                    /**< Scheduler instance */

/**
 * Tasks instances
 */
SonarTask* sonarT0;
ButtonTask* buttonT0;
BuzzerTask* buzzerT0;
LedTask* ledT0;
LedPwmTask* ledPwmT0;
LedRgbTask* ledRgbT0;


void setup() {
    msgService.init(BAUD, "JimmyChallenge", pContext);
    sched.init(100);

    pContext = new Context(MAX_DISTANCE_SONAR, new Multiplexer(muxChannel, NUM_MUX_CHANNEL));
    pContext->newRandomNumber();
    pContext->carousel(50, 50);

    /** Sonar task */
    sonarT0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    sonarT0->init(50, [] {
        if(!pContext->isGameOver()) {
            sonarT0->playLevel();
        } else {
            msgService.sendMsg("Gioco Finito!!!", "all");
            msgService.sendCode(500, "all", "status");
            pContext->setGameOver(true);
            pContext->carousel(50,50);
        }
    });
    sched.addTask(sonarT0);

    //** ButtonTask
    buttonT0 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    buttonT0->init(50, [] {
        bool buttonState = buttonT0->btn->readBool();
        if(!pContext->isGameOver()) {
            pContext->setButtonPressed(buttonState);
            if(buttonState) {
                msgService.sendMsg("Secret number " + String(pContext->getSecret()), "all");
            }
        } else {
            // necessario per la mario easter egg...
            pContext->setButtonPressed(buttonState);
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
        } else {
            // mario easter egg...
            if(pContext->isButtonPressed()) {
                buzzerT0->buzzer->playSound(2);
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
            for (int i = 5; i < 255; i++) {
                ledPwmT0->ledPwm->setIntensity(i);
                delay(3);
            }
            ledPwmT0->ledPwm->switchOff();
        }
    });
    sched.addTask(ledPwmT0);

    //** LedPwmTask
    ledRgbT0 = new LedRgbTask(LED_RGB_R, LED_RGB_G, LED_RGB_B, pContext);
    ledRgbT0->init(50, [] {
        // analogWrite in Arduino Uno in not fully compatible with new avrdude which use timer (on PlatformIO)
        if(!pContext->isGameOver()) {
            if (pContext->isLockpicking()) {
                switch (pContext->getDangerLevel()) {
                case 0: ledRgbT0->ledRgb->setColor(0, 0, 255); break;                 // blue = alert
                case 1: ledRgbT0->ledRgb->setColor(0, 255, 0); break;                 // green = lucchetto aperto
                case 2: ledRgbT0->ledRgb->setColor(255, 255, 0); break;               // yellow = lieve pericolo rottura
                case 3: ledRgbT0->ledRgb->setColor(255, 165, 255); break;             // pink = forte pericolo rottura
                case 4: ledRgbT0->ledRgb->setColor(255, 0, 0); break;                 // red == lucchetto rotto
                }
            } else {
                ledRgbT0->ledRgb->setColor(0, 130, 130);
            }
        }
    });
    sched.addTask(ledRgbT0);
} // end setup()

void loop() {
    sched.schedule();
}
