#ifndef __LIGHT_PWM__
#define __LIGHT_PWM__

#include "Light.h"

class LightPwm : public Light {
public:
  virtual void setIntensity(int) = 0;
};

#endif
