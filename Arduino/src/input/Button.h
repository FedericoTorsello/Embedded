#ifndef __BUTTON__
#define __BUTTON__

#include "../interface/Input.h"

class Button : public Input {
public:
    Button(int, unsigned long);
    bool readBool();
protected:
    int pin;
    int lastDebounceTime;  // the last time the output pin was toggled
    // the following variables are long's because the time, measured in miliseconds,
    // will quickly become a bigger number than can be stored in an int.
    int debounceDelay;    // the debounce time; increase if the output flickers
private:
    // constants won't change. They're used here to
    // set pin numbers:
    // const int buttonPin = 2;    // the number of the pushbutton pin

    // Variables will change:
    int lastButtonState;   // the previous reading from the input pin
    int buttonState;             // the current reading from the input pin

};

#endif
