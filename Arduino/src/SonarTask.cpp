#include "SonarTask.h"

SonarTask::SonarTask(int trigPin, int echoPin, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->pContext = pContext;
    NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
}

void SonarTask::init(int period) {
    Task::init(period);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void SonarTask::tick() {
    Serial.println("OK");
    // int uS = sonar->ping();
    // int distance = uS / US_ROUNDTRIP_CM;
    // int thresold = 20;
    // //int thresold = pContext->readRandom();
    // if (distance + DELTA < thresold && distance - DELTA > thresold) {
    //     Serial.println(distance);
    // }else {
    //     Serial.println("DIO CANE");
    // }
}
