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
    uint16_t secretDistance = pContext->getRandomNumber();
    uint16_t currentLevel = pContext->getLevel();

    msgService.sendMsg("d" + String(currentDistance), TO_REMOTE);
    if(currentDistance <= (secretDistance + delta)
       && currentDistance >= (secretDistance - delta)) {
        pContext->setPadlockDetected(true);
        timeFound = (millis()/1000) - timeOut;     // inizializzazione a zero
        switch (timeFound) {
        case 0:
            if (lockOpen) {
                msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", "debug");
                msgService.sendMsg("418", TO_REMOTE);
                lockOpen = false;
                pContext->setPadlockOpen(false);
                pContext->setStatoDiScasso(false);
                pContext->setNewLevel();
                delta = pContext->getDelta();
            } else
                msgService.sendMsg("101", TO_REMOTE);
            break;
        case 1:
            msgService.sendMsg("101", TO_REMOTE);
            break;
        case 2:
            msgService.sendMsg("102", TO_REMOTE);
            break;
        case 3:
            msgService.sendMsg("103", TO_REMOTE);
            break;
        case 4:
            msgService.sendMsg("104", TO_REMOTE);
            pContext->setDangerLevel(1);
            pContext->setStatoDiScasso(true);
            break;
        case 5:
            msgService.sendMsg("104", TO_REMOTE);
            pContext->setDangerLevel(1);
            break;
        case 6:
            msgService.sendMsg("105", TO_REMOTE);
            pContext->setDangerLevel(0);
            lockOpen = true;
            break;
        case 7:
            msgService.sendMsg("201", TO_REMOTE);
            pContext->setDangerLevel(0);
            break;
        case 8:
            msgService.sendMsg("202", TO_REMOTE);
            pContext->setDangerLevel(2);
            break;
        case 9:
            msgService.sendMsg("203", TO_REMOTE);
            pContext->setDangerLevel(3);
            break;
        case 10:
            msgService.sendMsg("204", TO_REMOTE);
            lockOpen = false;
            pContext->setDangerLevel(4);
            pContext->setPadlockOpen(false);
            break;
        case 11:
            msgService.sendMsg("205", TO_REMOTE);
            pContext->setDangerLevel(4);
            break;
        default: break;
        }
    } else {
        timeOut = millis()/1000;
        pContext->setPadlockDetected(false);
        pContext->setStatoDiScasso(false);
    }
}
