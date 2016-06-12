#ifndef __LED__
#define __LED__

#include "../interface/Light.h"

/** Class to manage a led */
class Led : public interface::Light {
public:
    Led(int);
protected:
    void switchOn();
    void switchOff();
    int pin;
};

#endif
