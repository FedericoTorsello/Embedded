#ifndef __LEDTASK__
#define __LEDTASK__

#include "../task/Task.h"
#include "../output/Led.h"
#include "../control/Context.h"

class LedTask : public Task {
public:
    LedTask(int, Context *);
    interface::Light* led;

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
