#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "Task.h"
#include "Button.h"
#include "Context.h"
#include "Arduino.h"

class ButtonTask : public Task {
public:
    ButtonTask(int, Context *);
    void init(int);
    void tick();
private:
    int pin;
    Button *btn;
    Context *pContext;
};

#endif
