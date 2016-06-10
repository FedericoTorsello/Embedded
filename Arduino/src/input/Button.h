#ifndef __BUTTON__
#define __BUTTON__

#include "../interface/Input.h"

class Button : public interface::Input {
public:
    Button(int, unsigned long);
    bool readBool();
private:
    bool buttonState = false;
    unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
    unsigned long debounceDelay;
protected:
    int pin;
};

#endif
