#ifndef __LED_PWM__
#define __LED_PWM__

#include "../interface/LightPwm.h"
#include "../interface/Light.h"
#include "Led.h"

/** Class to manage a led with support for pwm */
class LedPwm :  public interface::LightPwm, public Led {
public:
    LedPwm(int);
    LedPwm(int, int);
    void setIntensity(uint8_t);
    void switchOn();
    void switchOff();
private:
};

#endif
