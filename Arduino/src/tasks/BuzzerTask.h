#ifndef __BUZZERTASK__
#define __BUZZERTASK__

#include "../interface/Task.h"
#include "../output/Buzzer.h"
#include "../control/Context.h"

class BuzzerTask : public Task {
public:
    BuzzerTask(int, Context *);
    void init(int, void (*)());
    void tick();
    Buzzer *buzzer;
private:
    void (*_f)();
    void foo() {
        _f();
    }
    Context *pContext;
protected:
    int pin;
};

#endif
