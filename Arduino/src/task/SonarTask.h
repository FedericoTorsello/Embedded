#ifndef __SONARTASK__
#define __SONARTASK__

#include "../task/Task.h"
#include "../input/Sonar.h"
#include "../control/Context.h"
#include "../output/MessageService.h"

class SonarTask : public Task {
public:
    SonarTask(int, int, int, Context *);
    interface::Input* sonar;

    void init(int, void (*)());
    void tick();
    void printDistance();

    unsigned long timer1 = 0;
    unsigned long timer2 = 0;
    unsigned long timer3 = 0;
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
    int maxDist;
};

#endif
