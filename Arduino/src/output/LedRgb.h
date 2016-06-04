#ifndef __LED_RGB__
#define __LED_RGB__

#include "../interface/LightPwm.h"
#include "LedPwm.h"

class LedRgb {
public:
    LedRgb(int, int, int);
    void setColor(int, int, int);
private:
    LedPwm *red;
    LedPwm *green;
    LedPwm *blue;
protected:
    void switchOn();
    void switchOff();
};
#endif
