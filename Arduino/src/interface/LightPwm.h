#ifndef __LIGHT_PWM__
#define __LIGHT_PWM__

#include "Light.h"

namespace interface {

/**Interface for devices that use a dimmable light as a feedback */
class LightPwm : public interface::Light {
public:
    virtual void setIntensity(uint8_t) = 0;
};

}

#endif
