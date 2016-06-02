#ifndef __LEDRGBTASK__
#define __LEDRGBTASK__

#include "../task/Task.h"
#include "../output/LedRgb.h"
#include "../control/Context.h"

class LedRgbTask : public Task {
public:
    LedRgbTask(int, int, int, Context *);
    void init(int, void (*)());
    void tick();

    LedRgb *ledRgb;
private:
    void (*_f)();
    void foo() {
        _f();
    }

    Context *pContext;
protected:
    int pin1;
    int pin2;
    int pin3;
};

#endif
