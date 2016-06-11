#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../task/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

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
