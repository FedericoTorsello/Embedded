#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "../task/Task.h"
#include "../output/LedPwm.h"
#include "../control/Context.h"

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
