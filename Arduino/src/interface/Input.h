#ifndef __INPUT__
#define __INPUT__

#include "Arduino.h"

class Input {
public:
        virtual bool readBool() {
                return false;
        };
        virtual int readDistance() {
                return 0;
        };
};

#endif
