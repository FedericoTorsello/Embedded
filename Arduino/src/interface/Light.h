#ifndef __LIGHT__
#define __LIGHT__

#include "Arduino.h"

namespace interface {

/** Interface for devices that use light as a feedback */
class Light {
public:
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
};

}

#endif
