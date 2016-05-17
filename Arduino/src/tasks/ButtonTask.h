#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../interface/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

class ButtonTask : public Task {
public:
    ButtonTask(int, unsigned long, Context *);
    void init(int);
    void tick();
private:
    Button *btn;
    Context *pContext;
protected:
    int pin;
    unsigned long debounceDelay;
};

#endif
