#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "../task/Task.h"
#include "../output/LedPwm.h"
#include "../control/Context.h"

/** Class to manage the behaviour of a led pwm */
class LedPwmTask : public Task {
public:
    LedPwmTask(int, Context *);
    interface::LightPwm *ledPwm;

    void init(int, void (*)());
    void tick();
private:
    Context *pContext;
    void (*_f)();
    void lambdaTick() {
        _f();
    }
protected:
    int pin;
};

#endif
