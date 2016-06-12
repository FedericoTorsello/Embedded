#ifndef __AUDIO__
#define __AUDIO__

#include "Arduino.h"

namespace interface {

/** Interface for audio devices */
class Audio {
public:
    virtual void playSound(int) = 0;
};

}

#endif
