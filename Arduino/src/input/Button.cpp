#include "Button.h"

/** @brief ###Initialize the button and set init config */
Button::Button(const int pin, unsigned long debounceDelay) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    pinMode(pin,INPUT_PULLUP);
}

/** @brief ###Read a state from the hardware button
 *
 * When the button is pressed read the state and avoid debouncing
 */
bool Button::readBool() {
    buttonState = !digitalRead(pin);
    // When the state change record the time
    if (buttonState != true) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }
    // If the state changed after a short period of time to avoid noise
    if ((millis() - lastDebounceTime) >= debounceDelay) {
        return true;
    } else {
        return false;
    }
}
