#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "../interface/Task.h"
#include "../output/LedPwm.h"
#include "../control/Context.h"

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
