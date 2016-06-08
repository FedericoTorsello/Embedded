#ifndef __SONAR__
#define __SONAR__

#include "NewPing.h"
#include "../interface/Input.h"

class Sonar : public interface::Input {
public:
    Sonar(int, int, int);

protected:
    NewPing *mySonar;

    int readDistance();
};

#endif
