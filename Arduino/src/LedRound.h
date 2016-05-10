#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Arduino.h"

class LedRound : public Light {
public:
    LedRound(int pin);
    void switchOn();
    void switchOff();
protected:
    int pin;
};

#endif
