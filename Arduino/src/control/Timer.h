#ifndef __TIMER__
#define __TIMER__

#include "Arduino.h"

class Timer {
public:
        Timer();
        void setupFreq(int);
        /* period in ms */
        void setupPeriod(int);
        void waitForNextTick();
};


#endif
