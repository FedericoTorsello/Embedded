#ifndef __LEDTASK__
#define __LEDTASK__

#include "../interface/Task.h"
#include "../output/Led.h"
#include "../control/Context.h"

class LedTask : public Task {
public:
    LedTask(int, Context *);
    void init(int);
    void tick(void (*f)());
    Light* led;

private:
    int pin;

    Context* pContext;
};

#endif
