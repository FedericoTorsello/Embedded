#ifndef __LEDTASK__
#define __LEDTASK__

#include "../interface/Task.h"
#include "../output/Led.h"
#include "../control/Context.h"

class LedTask : public Task {
public:
        LedTask(int, Context *);
        void init(int);
        void tick();
private:
        int pin;
        Light* led;
        Context* pContext;
};

#endif
