#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "LedPwm.h"
#include "Context.h"
#include "Arduino.h"

class LedTask : public Task {
public:
    LedTask(int pin, Context* pContext);
    void init(int period);
    void tick();
private:
    int pin;
    LightPwm* led;
    Context* pContext;
};

#endif
