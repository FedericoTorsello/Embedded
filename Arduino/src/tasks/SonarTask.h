#ifndef __SONARTASK__
#define __SONARTASK__

#include "../interface/Task.h"
#include "../input/Sonar.h"
#include "../control/Context.h"
#include "../output/MessageService.h"

class SonarTask : public Task {
public:
    SonarTask(int, int, int, Context *);
    Input* sonar;

    void init(int, void (*)());
    void tick();
    void printDistance();

    int timer1 = 0;
    int timer2 = 0;
    int timer3 = 0;
    bool tempoCorretto = false;

private:
    Context *pContext;

    void (*_f)();
    void foo() {
        _f();
    }

protected:
    int echoPin;
    int trigPin;
    int MAX_DISTANCE;
};

#endif
