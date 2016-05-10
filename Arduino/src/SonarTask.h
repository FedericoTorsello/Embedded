#ifndef __SONARTASK__
#define __SONARTASK__

#include "Task.h"
#include "Context.h"
#include "Arduino.h"
#include "NewPing.h"

class SonarTask : public Task {
private:
    Context *pContext;
    NewPing *sonar;
    int echoPin;
    int trigPin;
    int startTime = 0;
    int endTime = 0;
    /* errore di lettura */
    const int DELTA = 4;
    int MAX_DISTANCE = 100;
    const int MIN_TIME = 500;
    const int MAX_TIME = 1000;
public:
    SonarTask(int trigPin, int echoPin, int maxDist, Context *pContext);
    void init(int period);
    void tick();
    void printPadlockState();
};

#endif
