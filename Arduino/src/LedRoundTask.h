#ifndef __LEDROUNDTASK__
#define __LEDROUNDTASK__

#include "Task.h"
#include "LedRound.h"
#include "Context.h"
#include "Arduino.h"

class LedRoundTask : public Task {
public:
    LedRoundTask(int pin, Context* pContext);
    void init(int period);
    void tick();
private:
    int pin;
    Light* led;
    Context* pContext;
};

#endif
