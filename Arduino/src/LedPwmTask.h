#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "Task.h"
#include "LedPwm.h"
#include "Context.h"
#include "Arduino.h"

class LedPwmTask : public Task {
public:
    LedPwmTask(int, Context *);
    void init(int);
    void tick();
private:
    int pin;
    LightPwm *ledPwm;
    Context *pContext;
};

#endif
