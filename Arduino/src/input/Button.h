#ifndef __BUTTON__
#define __BUTTON__

#include "../interface/Input.h"

class Button : public interface::Input {
public:
    Button(int, unsigned long);
    bool readBool();

private:
    bool buttonState = false;   // stato letto dal pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
    unsigned long debounceDelay; // INIZIALIZZATA DAL COSTRUTTORE

protected:
    int pin;
};

#endif
