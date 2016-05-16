#ifndef __SONARTASK__
#define __SONARTASK__

#include "../interface/Task.h"
#include "../input/Sonar.h"
#include "../control/Context.h"

class SonarTask : public Task {
public:
        SonarTask(int, int, int, Context *);
        void init(int);
        void tick();

private:
        int echoPin;
        int trigPin;
        int MAX_DISTANCE;

        int startTime = 0;
        int endTime = 0;
        int inc;
        int t, t2, t3;
        /* errore di lettura */
        const int DELTA = 4;
        const int indovina = 20;
        const int MIN_TIME = 500;
        const int MAX_TIME = 1000;

        bool tempoCorretto = false;
        bool padlockOpen = false;

        Input* sonar;
        Context *pContext;

        void printPadlockState();
};

#endif
