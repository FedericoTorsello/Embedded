#ifndef __BUTTON__
#define __BUTTON__

#include "Input.h"

class Button: public Input {
public:
  Button(int pin);
  bool readBool();
protected:
  int pin;
};

#endif
