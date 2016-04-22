#include "Arduino.h"

#ifndef __INPUT__
#define __INPUT__

class Input {
public:
    virtual bool readBool() {
        return false;
    };
    virtual String readString() {
        return "";
    };
};

#endif
