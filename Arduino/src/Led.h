#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Arduino.h"

class Led : public Light {
public:
    Led(int);
    void switchOn();
    void switchOff();
protected:
    int pin;
};

#endif
