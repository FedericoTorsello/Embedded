#ifndef __LEDROUNDTASK__
#define __LEDROUNDTASK__

#include "Task.h"
#include "Multiplexer.h"
#include "Context.h"
#include "Arduino.h"

class LedRoundTask : public Task {
public:
    LedRoundTask(int *, int, Context *);
    void init(int);
    void tick();
private:
    int *pins;
    int size;
    Multiplexer *led;
    Context* pContext;
};

#endif
