#include "SonarTask.h"

SonarTask::SonarTask(int trigPin, int echoPin, int maxDist, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->MAX_DISTANCE = maxDist;
    this->pContext = pContext;
    // set the sonar, [timeout]
    this->sonar = new NewPing(this->trigPin, this->echoPin, this->MAX_DISTANCE);
}

void SonarTask::init(int period) {
    Task::init(period);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void SonarTask::tick() {
    // If game is started
    if (pContext->getGame()) {
        // result from sonar
        int distance = sonar->ping() / US_ROUNDTRIP_CM;
        // distance to guess
        int distanceGuess = pContext->getDistanceGuess();
        distanceGuess = 10;
        if(distance <= distanceGuess + DELTA && distance >= distanceGuess - DELTA) {
            // Correct distance, check time
            endTime = millis();
            if (endTime - startTime >= MIN_TIME) {
                if (endTime - startTime <= MAX_TIME) {
                    pContext->setDetectedObj(30);
                    Serial.println("DENTRO");
                } else
                    Serial.println("TRPP DEN");
            }
        } else {
            pContext->setNoObjDetected();
            startTime = millis();
        }
    }
}
