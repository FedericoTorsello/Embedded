#ifndef __LEDTASK__
#define __LEDTASK__

#include "../task/Task.h"
#include "../output/Led.h"
#include "../control/Context.h"

class LedTask : public Task {
public:
    LedTask(int, Context *);
    void init(int, void (*)());
    void tick();
    interface::Light* led;
    
private:
    void (*_f)();
    void foo() {
        _f();
    }
    Context* pContext;
protected:
    int pin;
};

#endif
