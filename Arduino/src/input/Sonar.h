#ifndef __SONAR__
#define __SONAR__

#include "NewPing.h"
#include "../interface/Input.h"

class Sonar : public interface::Input {
public:
    Sonar(int trigPin, int echoPin, int maxDist);
    int readDistance();

protected:
    NewPing *mySonar;
    int echoPin;
    int trigPin;
    int MAX_DISTANCE;

};

#endif
