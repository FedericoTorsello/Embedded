#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "Task.h"
#include "Button.h"
#include "Context.h"
#include "Arduino.h"

class ButtonTask : public Task {
public:
    ButtonTask(int pin, Context* pContext);
    void init(int period);
    void tick();
private:
    int pin;
    Button *btn;
    Context *pContext;
};

#endif
