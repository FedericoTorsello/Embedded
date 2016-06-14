#include "control/Scheduler.h"
#include "output/MessageService.h"
#include "task/SonarTask.h"
#include "task/LedTask.h"
#include "task/LedPwmTask.h"
#include "task/LedRgbTask.h"
#include "task/ButtonTask.h"
#include "task/BuzzerTask.h"

const int BAUD = 9600;                                  /**< Serial baud rate */
const uint8_t MAX_DISTANCE_SONAR = 50;                  /**< Maximum distance game */
const uint8_t DEBOUNCE_DELAY = 30;                      /**< Button debounce delay */
const uint8_t NUM_MUX_CHANNEL = 4;                      /**< Number of input channels for the multiplexer */

const int BUTTON_PIN = 2;                               /**< Input digital from button */
int muxChannel[NUM_MUX_CHANNEL] = {4, 5, 12, 13};       /**< Input channels for the multiplexer */
const uint8_t TRIG_PIN = 7;                             /**< Trigger pin of sonar */
const uint8_t ECHO_PIN = 8;                             /**< Echo pin of sonar*/

const uint8_t BUZZER_PIN = 3;                           /**< Input pin for buzzer */
const uint8_t LED_PWM = 6;                              /**< Input pwm for led */
const uint8_t LED_RGB_R = 9;                            /**< Input pwm for color red of RGB led */
const uint8_t LED_RGB_G = 10;                           /**< Input pwm for color green of RGB led */
const uint8_t LED_RGB_B = 11;                           /**< Input pwm for color blue of RGB led */

Context* pContext;                                      /**< Context instance */
Scheduler sched;                                        /**< Scheduler instance */

/**
 * Tasks instances
 */
SonarTask* sonarT0;
ButtonTask* buttonT0;
BuzzerTask* buzzerT0;
LedTask* ledT0;
LedPwmTask* ledPwmT0;
LedRgbTask* ledRgbT0;

/** @brief Set and init all tasks before start.
 *
 * Configuration of all tasks, scheduler and the service for serial reading/writing;
 * all behaviours of tasks are define by a lambda and execute by the scheduler for a defined time.
 */
void setup() {
    // Start the serial interface
    msgService.init(BAUD, F("JimmyChallenge"));
    sched.init(100);

    // Init the context and the multiplexer
    pContext = new Context(MAX_DISTANCE_SONAR, new Multiplexer(muxChannel, NUM_MUX_CHANNEL));
    pContext->newRandomNumber();
    // Show a nice effect
    pContext->carousel(50, 50);

    /** @brief ###Sonar Task
     *
     * This task reads the distance from the sonar and set the context's
     * variables to play the game.
     */
    sonarT0 = new SonarTask(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_SONAR, pContext);
    sonarT0->init(50, [] {
        if(!pContext->isGameOver()) {
            // Set up and config a level
            sonarT0->playLevel();
        } else {
            // When the game is finished
            msgService.sendMsg(F("Gioco Finito!!!"), F("all"));
            msgService.sendInfo(0, 500, pContext->getDangerLevel(), F("remote"));
            pContext->carousel(50,50);
        }
    });
    // Add the task to the scheduler tasks' list
    sched.addTask(sonarT0);

    /** @brief ###Button Task
     *
     * This taks reads the state of a button paying attention to avoid debounced fake values.
     */
    buttonT0 = new ButtonTask(BUTTON_PIN, DEBOUNCE_DELAY, pContext);
    buttonT0->init(50, [] {
        bool buttonState = buttonT0->btn->readBool();
        if(!pContext->isGameOver()) {
            pContext->setButtonPressed(buttonState);
            if(buttonState) {
                // print a debug message to easily find the distance to pick the lock
                msgService.sendMsg("Secret number " + String(pContext->getSecret()), F("all"));
            }
        } else {
            // Run the easter egg
            pContext->setButtonPressed(buttonState);
        }
    });
    sched.addTask(buttonT0);

    /** @brief ###Buzzer Task
     *
     * The buzzer plays two different tones to alert the user of the game status
     */
    buzzerT0 = new BuzzerTask(BUZZER_PIN, pContext);
    buzzerT0->init(50, [] {
        if(!pContext->isGameOver()) {
            if (pContext->isPadlockDetected()) {
                buzzerT0->buzzer->playSound(0);
            } else {
                buzzerT0->buzzer->playSound(1);
            }
        } else {
            // Execute the easter egg
            if (pContext->isButtonPressed()) {
                buzzerT0->buzzer->playSound(2);
            }
        }
    });
    sched.addTask(buzzerT0);

    /** @brief ###LED Task
     *
     * When the user found the correct position the led stops blinking and remains lighted up
     */
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

    /** @brief ###LedPWm Task
     *
     * When the user has not found the correct position the led blinks
     */
    ledPwmT0 = new LedPwmTask(LED_PWM, pContext);
    ledPwmT0->init(50, [] {
        if (!pContext->isPadlockOpen() && !pContext->isPadlockDetected()) {
            for (int i = 64; i < 255; i++) {
                ledPwmT0->ledPwm->setIntensity(i);
            }
            ledPwmT0->ledPwm->switchOff();
        }

        if (pContext->isGameOver()) {
            for (int i = 10; i < 255; i++) {
                ledPwmT0->ledPwm->setIntensity(i);
                delay(3);
            }
            ledPwmT0->ledPwm->switchOff();
        }
    });
    sched.addTask(ledPwmT0);

    /** @brief ###LedRGB Task
     *
     * This tasks alert the user fo the current lockpicking status:
     * when the led is green the lock is open
     */
    ledRgbT0 = new LedRgbTask(LED_RGB_R, LED_RGB_G, LED_RGB_B, pContext);
    ledRgbT0->init(50, [] {
        // analogWrite in Arduino Uno in not fully compatible with new avrdude which use timer (on PlatformIO)
        if(!pContext->isGameOver()) {
            if (pContext->isLockpicking()) {
                switch (pContext->getDangerLevel()) {
                case 0: ledRgbT0->ledRgb->setColor(0, 0, 255); break;                 // blue = alert
                case 1: ledRgbT0->ledRgb->setColor(0, 255, 0); break;                 // green = lock open
                case 2: ledRgbT0->ledRgb->setColor(255, 255, 0); break;               // yellow = first warning
                case 3: ledRgbT0->ledRgb->setColor(255, 165, 255); break;             // pink = second warning
                case 4: ledRgbT0->ledRgb->setColor(255, 0, 0); break;                 // red == jimmy broken
                }
            } else {
                ledRgbT0->ledRgb->setColor(0, 130, 130);                              // light blue = default color
            }
        }
    });
    sched.addTask(ledRgbT0);
} // end setup()

/** @brief Start the main Arduino loop
 *
 * The scheduler runs all tasks sequentially
 */
void loop() {
    sched.schedule();
}
