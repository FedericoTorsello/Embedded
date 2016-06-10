#include "SonarTask.h"

SonarTask::SonarTask(const int trigPin, const int echoPin, const int maxDist, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->maxDist = maxDist;
    this->pContext = pContext;
    this->sonar = new Sonar(this->trigPin, this->echoPin, this->maxDist);
    this->delta = pContext->getDelta();
}

void SonarTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void SonarTask::tick() {
    Task::callTick();
}

void SonarTask::playLevel() {
    String TO_REMOTE = "remote";
    String TO_ALL = "all";
    currentDistance = uint16_t(sonar->readDistance());
    pContext->setCurrentDistance(currentDistance);
    uint16_t secretDistance = pContext->getSecret();
    uint16_t currentLevel = pContext->getLevel();
    uint16_t status = 0;
    int feedbackDistance = 0;


    feedbackDistance = abs(int(currentDistance) - int(secretDistance));
    if (feedbackDistance == 0)
        feedbackDistance = 0;
    else if (currentDistance == 0)
        feedbackDistance = 100;
    msgService.sendCode(feedbackDistance, TO_REMOTE, "distance");

    if(currentDistance <= (secretDistance + delta)
       && currentDistance >= (secretDistance - delta)) {
        pContext->setPadlockDetected(true);
        timeFound = (millis()/1000) - timeOut;     // inizializzazione a zero
        switch (timeFound) {
        case 0:
            if (lockOpen) {
                msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", "debug");
                pContext->setNewLevel();
                if (!pContext->isGameOver()) {
                    status = 300 + currentLevel + 1;
                    lockOpen = false;
                    pContext->setPadlockOpen(false);
                    pContext->setLockpicking(false);
                    delta = pContext->getDelta();
                }
            } else
                status = 101;
            break;
        case 1:
            status = 101;
            break;
        case 2:
            status = 102;
            break;
        case 3:
            status = 103;
            break;
        case 4:
            status = 104;
            pContext->setDangerLevel(0);
            pContext->setLockpicking(true);
            break;
        case 5:
            status = 104;
            pContext->setDangerLevel(0);
            break;
        case 6:
            status = 105;
            pContext->setDangerLevel(1);
            lockOpen = true;
            break;
        case 7:
            status = 201;
            pContext->setDangerLevel(1);
            break;
        case 8:
            status = 202;
            pContext->setDangerLevel(2);
            break;
        case 9:
            status = 203;
            pContext->setDangerLevel(3);
            break;
        case 10:
            status = 204;
            lockOpen = false;
            pContext->setDangerLevel(4);
            pContext->setPadlockOpen(false);
            break;
        case 11:
            status = 205;
            pContext->setDangerLevel(4);
            break;
        }
        msgService.sendCode(status, TO_REMOTE, "status");
    } else {
        timeOut = millis()/1000;
        pContext->setPadlockDetected(false);
        pContext->setLockpicking(false);
        msgService.sendCode(0, TO_REMOTE, "status");
    }
}
