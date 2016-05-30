#ifndef __LEDPWMTASK__
#define __LEDPWMTASK__

#include "../task/Task.h"
#include "../output/LedPwm.h"
#include "../control/Context.h"

class LedPwmTask : public Task {
public:
    LedPwmTask(int, Context *);
    void init(int, void (*)());
    void tick();

    interface::LightPwm *ledPwm;
private:
    void (*_f)();
    void foo() {
        _f();
    }

    Context *pContext;
protected:
    int pin;
};

#endif
