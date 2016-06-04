#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../task/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

class ButtonTask : public Task {
public:
    ButtonTask(int, int, Context *);
    Button *btn;
    
    void init(int, void (*)());
    void tick();
private:
    Context *pContext;

    void (*_f)();
    void foo() {
        _f();
    }
protected:
    int pin;
    int debounceDelay;
};

#endif
