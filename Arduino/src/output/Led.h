#ifndef __LED__
#define __LED__

#include "../interface/Light.h"

class Led : public Light {
public:
    Led(int);
    void switchOn();
    void switchOff();
protected:
    int pin;
};

#endif
