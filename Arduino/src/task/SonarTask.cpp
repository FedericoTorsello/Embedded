#include "SonarTask.h"

SonarTask::SonarTask(int trigPin, int echoPin, int maxDist, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->maxDist = maxDist;
    this->pContext = pContext;
    this->sonar = new Sonar(this->trigPin, this->echoPin, this->maxDist);
}

void SonarTask::init(int period, void (*f)()) {
    this->_f = f;
    Task::init(period);
}

void SonarTask::tick() {
    Task::callFoo();
}

void SonarTask::playLevel(int currentLevel, int delta, int numSegreto){

    const String FROM_ARDUINO = pContext->getFrom();
    const String TO_REMOTE = pContext->getTo();
    bool statoDiScasso = false;
    int distance = sonar->readDistance();

    pContext->setCurrentDistance(distance);

    // print numero segreto da indovinare
    // msgService.sendMsg("Secret number " + String(numSegreto), FROM_ARDUINO, TO_REMOTE);

    // print distance
    // msgService.sendMsg("Distance " + String(distance), FROM_ARDUINO, TO_REMOTE);

    if(distance <= numSegreto + delta && distance >= numSegreto - delta && !pContext->isPadlockOpen()) {
        pContext->setPadlockDetected(true);
        pContext->setStatoDiScasso(false);

        timer1 = millis()/1000;
        timer1 = timer1 - timer2;     // inizializzazione a zero

        // girare la chia
        if(tempoCorretto && timer1 == 0) {
            msgService.sendMsg("Lucchetto livello " + String(currentLevel) + " APERTO", FROM_ARDUINO, TO_REMOTE);
            tempoCorretto = false;
            timer1 = 0;
            pContext->setPadlockOpen(false);
            pContext->setLevelToPlay(currentLevel);
        }

        if(timer1 <= 1 && !statoDiScasso) {
            msgService.sendMsg("Hai trovato il lucchetto", FROM_ARDUINO, TO_REMOTE);
        } else if(timer1 == 2) {
            msgService.sendMsg("Bene, stai calmo", FROM_ARDUINO, TO_REMOTE);
        } else if (timer1 == 3 || timer1 == 4) {
            msgService.sendMsg("Bisogna stare attenti...", FROM_ARDUINO, TO_REMOTE);
        } else if (timer1 > 4) {
            pContext->setStatoDiScasso(true);
        }

        if(pContext->isStatoDiScasso()) {
            timer3 = millis()/1000;
            timer3 = timer3 - timer2 - 4;      // -4 per far partire il tempo ledT0 da zero

            switch (timer3) {
            case 1:
                msgService.sendMsg("Stai scassinando il lucchetto", FROM_ARDUINO, TO_REMOTE);
                break;
            case 2:
                msgService.sendMsg("Ancora un po' di pazienza", FROM_ARDUINO, TO_REMOTE);
                break;
            case 3:
                msgService.sendMsg("Livello " + String(currentLevel) + " passato :D", FROM_ARDUINO, TO_REMOTE);
                pContext->setDangerLevel(0);
                tempoCorretto = true;
                break;
            case 4:
                msgService.sendMsg("...però non restare fermo...", FROM_ARDUINO, TO_REMOTE);
                pContext->setDangerLevel(1);
                tempoCorretto = true;
                break;
            case 5:
                msgService.sendMsg("...stai rishiando la rottura...", FROM_ARDUINO, TO_REMOTE);
                pContext->setDangerLevel(2);
                tempoCorretto = true;
                break;
            case 6:
                msgService.sendMsg("Attento! Lo rompi davvero!", FROM_ARDUINO, TO_REMOTE);
                pContext->setDangerLevel(3);
                tempoCorretto = true;
                break;
            case 7:
                msgService.sendMsg("Nooo, l'hai rotto! Devi riprovare", FROM_ARDUINO, TO_REMOTE);
                tempoCorretto = false;
                pContext->setDangerLevel(4);
                pContext->setPadlockOpen(false);
                break;
            case 8:
                msgService.sendMsg("Devi ricominciare!", FROM_ARDUINO, TO_REMOTE);
                pContext->setDangerLevel(4);
                break;
            default: break;
            }
        }
    } else {
        if(!pContext->isPadlockOpen()) {
            timer2 = millis()/1000;
            // msgService.sendMsg("NON APERTO", FROM_ARDUINO, TO_REMOTE);
            pContext->setPadlockOpen(false);
            pContext->setPadlockDetected(false);
        }
    }
}
