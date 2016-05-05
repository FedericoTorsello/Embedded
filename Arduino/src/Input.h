#include "Arduino.h"

#ifndef __INPUT__
#define __INPUT__

class Input {
public:
    virtual bool readBool();
    virtual String readString();
};

#endif
