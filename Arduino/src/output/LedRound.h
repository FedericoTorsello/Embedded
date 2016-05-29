#ifndef __LEDROUND__
#define __LEDROUND__

#include "../interface/Light.h"
#include "Led.h"

class LedRound : public interface::Light {
public:
    LedRound(int *, int);
    void switchOn();
    void switchOff();
    void switchOn(int *, int);
    void switchOff(int *, int);
private:
    int size;
    int *pins;
    Led *leds;
};

#endif
