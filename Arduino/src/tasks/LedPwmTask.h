#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "../interface/Task.h"
#include "../output/LedPwm.h"
#include "../control/Context.h"

class LedPwmTask : public Task {
public:
    LedPwmTask(int, Context *);
    void init(int, void (*)());
    void tick();
private:
    void (*_f)();
    void foo() {
        _f();
    }
    LightPwm *ledPwm;
    Context *pContext;
protected:
    int pin;
};

#endif
