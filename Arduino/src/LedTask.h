#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "Led.h"
#include "Context.h"
#include "Arduino.h"

class LedTask : public Task {
public:
    LedTask(int, Context *);
    void init(int);
    void tick();
private:
    int pin;
    Light* led;
    Context* pContext;
};

#endif
