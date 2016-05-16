#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin, int MAX_DISTANCE) {
        this->trigPin = trigPin;
        this->echoPin = echoPin;
        this->MAX_DISTANCE = MAX_DISTANCE;
        this->mySonar = new NewPing(trigPin, echoPin, MAX_DISTANCE);
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
}


int Sonar::readDistance(){
        return mySonar->ping_cm();
}
