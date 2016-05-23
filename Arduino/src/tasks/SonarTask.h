#ifndef __SONARTASK__
#define __SONARTASK__

#include "../interface/Task.h"
#include "../input/Sonar.h"
#include "../control/Context.h"
#include "../output/MessageService.h"

class SonarTask : public Task {
public:
    SonarTask(int, int, int, Context *);
    void init(int, void (*)());
    void tick();
    Input* sonar;
    void printDistance();
private:
    void (*_f)();
    void foo() {
        _f();
    }

    int echoPin;
    int trigPin;
    int MAX_DISTANCE;

    int distance;

    int startTime = 0;
    int endTime = 0;
    int inc;
    int t, t2, t3;
    /* errore di lettura */
    const int DELTA = 4;
    const int indovina = 20;

    bool tempoCorretto = false;

    Context *pContext;
};

#endif
