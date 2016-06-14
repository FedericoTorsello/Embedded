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
    this->lambdaTick();
}

void SonarTask::playLevel() {
    currentDistance = sonar->readDistance();
    pContext->setCurrentDistance(currentDistance);
    int secretDistance = pContext->getSecret();
    int currentLevel = pContext->getLevel();
    uint8_t delta = pContext->getDelta();
    int status = 0;
    int feedbackDistance = 0;

    feedbackDistance = abs(currentDistance - secretDistance);
    if (feedbackDistance == 0)
        feedbackDistance = 0;
    else if (currentDistance == 0)
        feedbackDistance = 100;

    if(currentDistance <= (secretDistance + delta)
       && currentDistance >= (secretDistance - delta)) {
        pContext->setPadlockDetected(true);
        timeFound = (millis()/1000) - timeOut;     // inizializzazione a zero
        switch (timeFound) {
        case 0:
            if (pContext->isPadlockOpen()) {
                msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", F("all"));
                pContext->setNewLevel();
                // if (!pContext->isGameOver()) {
                //     status = 300 + currentLevel + 1;
                    pContext->setPadlockOpen(false);
                    pContext->setLockpicking(false);
                // }
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
            pContext->setPadlockOpen(true);
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
            pContext->setDangerLevel(4);
            pContext->setPadlockOpen(false);
            break;
        case 11:
            status = 205;
            pContext->setDangerLevel(4);
            break;
        }
    } else {
        timeOut = millis()/1000;
        pContext->setPadlockDetected(false);
        pContext->setLockpicking(false);
    }
    msgService.sendInfo(currentDistance, status, currentLevel, F("remote"));
}
