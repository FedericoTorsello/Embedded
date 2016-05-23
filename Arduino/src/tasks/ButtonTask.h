#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "../interface/Task.h"
#include "../input/Button.h"
#include "../control/Context.h"

class ButtonTask : public Task {
public:
    ButtonTask(int, int, Context *);
    void init(int);
    void tick(void (*f)());
private:
    Button *btn;
    Context *pContext;
protected:
    int pin;
    int debounceDelay;
};

#endif
