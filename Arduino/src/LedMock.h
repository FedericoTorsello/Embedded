#ifndef __LEDMOCK__
#define __LEDMOCK__

#include "Light.h"

class LedMock: public Light {
public:
  LedMock(int pin);
  void switchOn();
  void switchOff();
protected:
  int pin;
};

#endif
