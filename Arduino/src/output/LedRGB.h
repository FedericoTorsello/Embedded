#ifndef __LED_RGB__
#define __LED_RGB__

#include "../interface/LightPwm.h"
#include "LedPwm.h"

class LedRGB {
public:
    LedRGB(int, int, int);
    void switchOn();
    void switchOff();
    void setColor(int, int, int);
private:
    LedPwm *red;
    LedPwm *green;
    LedPwm *blue;
};

#endif
