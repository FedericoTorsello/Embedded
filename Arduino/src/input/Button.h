#ifndef __BUTTON__
#define __BUTTON__

#include "../interface/Input.h"

/** Class to manage signals from a button */
class Button : public interface::Input {
public:
    Button(int, unsigned long);
    bool readBool();
private:
    bool buttonState = false;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay;
protected:
    int pin;
};

#endif
