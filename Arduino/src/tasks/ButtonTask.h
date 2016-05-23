#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../interface/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

class ButtonTask : public Task {
public:
    ButtonTask(int, int, Context *);
    void init(int, void (*)());
    void tick();
    Button *btn;
private:
    void (*_f)();
    void foo() {
        _f();
    }
    Context *pContext;
protected:
    int pin;
    int debounceDelay;
};

#endif
