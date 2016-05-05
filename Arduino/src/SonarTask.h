#ifndef __SONARTASK__
#define __SONARTASK__

#include "Task.h"
#include "Context.h"
#include "Arduino.h"
#include "NewPing.h"

class SonarTask : public Task {
public:
    SonarTask(int trigPin, int echoPin, Context *pContext);
    void init(int period);
    void tick();
private:
    NewPing *sonar;
    Context *pContext;
    int echoPin;
    int trigPin;
    const int MAX_DISTANCE = 100;
    /* errore di lettura */
    const int DELTA = 1;
};

#endif
