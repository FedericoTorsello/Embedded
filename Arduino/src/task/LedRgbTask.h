#ifndef __LEDRGBTASK__
#define __LEDRGBTASK__

#include "../task/Task.h"
#include "../output/LedRgb.h"
#include "../control/Context.h"

/** Class to manage the behaviour of a RGB led */
class LedRgbTask : public Task {
public:
    LedRgbTask(int, int, int, Context *);
    LedRgb *ledRgb;

    void init(int, void (*)());
    void tick();
private:
    Context *pContext;

    void (*_f)();
    void lambdaTick() {
        _f();
    }
protected:
    int pin1;
    int pin2;
    int pin3;
};

#endif
