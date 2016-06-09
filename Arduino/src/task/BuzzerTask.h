#ifndef __BUZZERTASK__
#define __BUZZERTASK__

#include "../task/Task.h"
#include "../output/Buzzer.h"
#include "../control/Context.h"

class BuzzerTask : public Task {
public:
    BuzzerTask(int, Context *);
    Buzzer *buzzer;

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
