#ifndef __TIMER__
#define __TIMER__

#include "Arduino.h"

class Timer {
public:
    Timer();
    /* period in ms */
    void setupPeriod(int);
    void waitForNextTick();
};


#endif
