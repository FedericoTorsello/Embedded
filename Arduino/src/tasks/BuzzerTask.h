#ifndef __BUZZERTASK__
#define __BUZZERTASK__

#include "../interface/Task.h"
#include "../output/Buzzer.h"
#include "../control/Context.h"

class BuzzerTask : public Task {
public:
    BuzzerTask(int, Context *);
    void init(int);
    void tick(void (*f)());
private:
    Buzzer *buzzer;
    Context *pContext;
protected:
    int pin;
};

#endif
