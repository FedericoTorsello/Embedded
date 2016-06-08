#include "Sonar.h"

Sonar::Sonar(const int trigPin, const int echoPin, const int maxDistance) {
    this->mySonar = new NewPing(trigPin, echoPin, maxDistance);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int Sonar::readDistance(){
    return mySonar->ping_cm();
}
