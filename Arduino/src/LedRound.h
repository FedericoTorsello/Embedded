#ifndef __LEDROUND__
#define __LEDROUND__

#include "Light.h"
#include "Arduino.h"

class LedRound : public Light {
public:
    LedRound(int *, int);
    void switchOn();
    void switchOff();
    void switchRoundOn(int *, int);
    void switchRoundOff(int *, int);
protected:
    int *pins;
private:
    int size;
};

#endif