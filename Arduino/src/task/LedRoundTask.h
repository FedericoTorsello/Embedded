#ifndef __LEDROUNDTASK__
#define __LEDROUNDTASK__

#include "../task/Task.h"
#include "../output/Multiplexer.h"
#include "../control/Context.h"

class LedRoundTask : public Task {
public:
    LedRoundTask(int *, int, Context *);
    void init(int, void (*)());
    void tick();
private:
    void (*_f)();
    void foo() {
        _f();
    }
    int *pins;
    int size;
    Multiplexer *led;
    Context* pContext;
};

#endif
