#include "SonarTask.h"

DetectObjTask::DetectObjTask(int trigPin, int echoPin, Context* pContext) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->pContext = pContext;
}

void DetectObjTask::init(int period) {
    Task::init(period);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void DetectObjTask::tick() {
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);

    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;

    // long rnd = random(5,50);
    // Serial.println("valore random " + String(rnd));

    // Level level;
    //
    // long rnd = level.genRndNumber(5,50);
    // if (d >= rnd - 5 && d <= rnd + 5){
    //   pContext->setDetectedObj(d);
    // } else {
    //   pContext->setNoObjDetected();
    // }
}
