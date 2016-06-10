#include "Button.h"

Button::Button(const int pin, unsigned long debounceDelay) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    //  INPUT_PULLUP: where HIGH means the sensor is off, and LOW means the sensor is on
    pinMode(pin,INPUT_PULLUP);
}

bool Button::readBool() {
    // read the state of the switch into a local variable:
    buttonState = !digitalRead(pin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:
    // If the switch changed, due to noise or pressing:
    if (buttonState != true) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) >= debounceDelay) {
        return true;
    } else {
        return false;
    }
}
