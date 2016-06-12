#ifndef __TIMER__
#define __TIMER__

#include "Arduino.h"

/**Class to manage Arduino internal timers */
class Timer {
public:
    Timer();
    void setupPeriod(int);
    void waitForNextTick();
};

#endif
