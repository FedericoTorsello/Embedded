#ifndef __BUTTON__
#define __BUTTON__

#include "../interface/Input.h"

class Button : public Input {
public:
        Button(int);
        bool readBool();
protected:
        int pin;
};

#endif
