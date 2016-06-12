#ifndef __SONARTASK__
#define __SONARTASK__

#include "../task/Task.h"
#include "../input/Sonar.h"
#include "../control/Context.h"
#include "../output/MessageService.h"

/** Class to manage the behaviour of the sonar */
class SonarTask : public Task {
public:
    SonarTask(int, int, int, Context *);
    interface::Input* sonar;
    void init(int, void (*)());
    void tick();
    void playLevel();
private:
    Context *pContext;
    unsigned long timeFound = 0;
    unsigned long timeOut = 0;
    uint16_t currentDistance = 0;
    uint8_t delta;

    void (*_f)();
    void lambdaTick() {
        _f();
    }
protected:
    int echoPin;
    int trigPin;
    int maxDist;
};

#endif
