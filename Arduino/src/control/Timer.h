#ifndef __TIMER__
#define __TIMER__

#include "Arduino.h"

class Timer {
public:
    Timer();
    void setupPeriod(int); // periodo in ms
    void waitForNextTick();
};

#endif
