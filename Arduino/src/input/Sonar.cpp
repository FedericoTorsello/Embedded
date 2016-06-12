#include "Sonar.h"

/** @brief ###Create a new object to read value from sonar using 'NewPing' library */
Sonar::Sonar(const int trigPin, const int echoPin, const int maxDistance) {
    this->mySonar = new NewPing(trigPin, echoPin, maxDistance);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

/** @brief ###Read the distance detected
 *
 * @return The distance value in centimeters
 */
int Sonar::readDistance(){
    return mySonar->ping_cm();
}
