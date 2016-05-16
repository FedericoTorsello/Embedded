#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../interface/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

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
