#ifndef __LEDROUNDTASK__
#define __LEDROUNDTASK__

#include "../interface/Task.h"
#include "../output/Multiplexer.h"
#include "../control/Context.h"

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
