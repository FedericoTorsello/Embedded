#ifndef __LIGHT_PWM__
#define __LIGHT_PWM__

#include "Light.h"

namespace interface {

class LightPwm : public interface::Light {
public:
    virtual void setIntensity(int) = 0;
};

}

#endif
