#include "DetectObjTask.h"
#include "Arduino.h"

const float vs = 331.5 + 0.6*20;

DetectObjTask::DetectObjTask(int trigPin, int echoPin, Context* pContext){
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->pContext = pContext;
}

void DetectObjTask::init(int period){
  Task::init(period);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void DetectObjTask::tick(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);

  float tUS = pulseIn(echoPin, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t*vs;
  if (d >= 0 && d <= pContext->getMaxDistance()){
    pContext->setDetectedObj(d);
  } else {
    pContext->setNoObjDetected();
  }
}
