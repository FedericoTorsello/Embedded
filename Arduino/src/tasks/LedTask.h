#ifndef __LEDTASK__
#define __LEDTASK__

#include "../interface/Task.h"
#include "../output/Led.h"
#include "../control/Context.h"

class LedTask : public Task {
public:
    LedTask(int, Context *);
    void init(int, void (*)());
    void tick();
    Light* led;

private:
    int pin;
    void (*_f)();
    void foo() {
        _f();
    }
    Context* pContext;
};

#endif
