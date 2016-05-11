#ifndef __LED_PWM__
#define __LED_PWM__

#include "Led.h"
#include "LightPwm.h"
#include "Arduino.h"

class LedPwm :  public LightPwm, public Led {
public:
    LedPwm(int);
    LedPwm(int, int);
    void switchOn();
    void switchOff();
    void setIntensity(int);
private:
    int currentIntensity;
    bool isOn;
};

#endif
