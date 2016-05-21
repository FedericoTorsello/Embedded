#ifndef __AUDIO__
#define __AUDIO__

#include "Arduino.h"

class Audio {
public:
    virtual void playSound(int, int, int) = 0;
    virtual void stopSound() = 0;
};

#endif
