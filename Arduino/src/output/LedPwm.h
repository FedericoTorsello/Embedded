#ifndef __LED_PWM__
#define __LED_PWM__

#include "../interface/LightPwm.h"
#include "../interface/Light.h"
#include "Led.h"

class LedPwm :  public interface::LightPwm, public Led {
public:
    LedPwm(int);
    LedPwm(int, int);
    void setIntensity(int);
    void switchOn();
    void switchOff();
private:
    int currentIntensity;
};

#endif
