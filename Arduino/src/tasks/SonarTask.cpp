#include "SonarTask.h"

SonarTask::SonarTask(int trigPin, int echoPin, int maxDist, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->MAX_DISTANCE = maxDist;
    this->pContext = pContext;
}

void SonarTask::init(int period) {
    Task::init(period);
    sonar = new Sonar(this->trigPin, this->echoPin, this->MAX_DISTANCE);
}

void SonarTask::tick() {
    int distance = sonar->readDistance();

    if(distance <= indovina + DELTA && distance >= indovina - DELTA && !padlockOpen) {

        t = millis()/1000;
        t = t - t2;         // inizializzazione a zero

        if(tempoCorretto && t == 0) {
            padlockOpen = true;
            printPadlockState();
        }

        switch (t) {
        case 1:
            Serial.println("hai trovato il lucchetto");
            break;

        case 2:
            Serial.println("ti stai avvicinando");
            break;

        case 3:
            Serial.println("ora bisogna stare attenti");
            break;

        case 4:
            Serial.println("ora bisogna stare attenti");
            break;
        }

        if (t >= 4) {
            t3 = millis()/1000;
            t3 = t3 - t2 - 4;             // -4 per far partire il tempo t3 da zero

            switch (t3) {
            case 1:
                Serial.println("stai scassinando il lucchetto");
                break;

            case 2:
                Serial.println("ancora un po' di pazienza");
                break;

            case 3:
                Serial.println("ce l'hai fatta!!! :D");
                tempoCorretto = true;
                break;
            }

            if(t3 >= 4 && t3 <= 5) {
                Serial.println("...però non restare fermo...");
                tempoCorretto = true;
            }

            if(t3 == 6) {
                Serial.println("Attento! rischi di romperlo!");
                tempoCorretto = true;
            }

            if(t3 >= 7) {
                Serial.println("Noooooo, l'hai rotto! Devi riprovare");
                tempoCorretto = false;
            }
        }
    }else{
        if(!padlockOpen) {
            t2 = millis()/1000;
            // printPadlockState();
        }
    }
}

void SonarTask::printPadlockState(){
    if(padlockOpen) {
        Serial.println("APERTO");
    }else{
        Serial.println("NON APERTO");
    }
}

void SonarTask::printDistance() {
    msgService.sendMsg(String(sonar->readDistance()), "arduino", "remote");
}
