#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../task/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

/** Class to create a task using the state of a button */
class ButtonTask : public Task {
public:
    ButtonTask(int, unsigned long, Context *);
    Button *btn;

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
    unsigned long debounceDelay;
};

#endif
