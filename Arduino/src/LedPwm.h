#ifndef __LED_PWM__
#define __LED_PWM__

#include "Led.h"
#include "LightPwm.h"

class LedPwm :  public LightPwm, public Led {
public:
    LedPwm(int pin);
    LedPwm(int pin, int intensity);
    void switchOn();
    void switchOff();
    void setIntensity(int v);
private:
    int currentIntensity;
    bool isOn;
};

#endif
