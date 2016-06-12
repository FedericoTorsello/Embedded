#ifndef __MULTIPLEXER__
#define __MULTIPLEXER__

#include "Arduino.h"

/** Class to manage a 16-channels multiplexer (CD4067B) */
class Multiplexer {
public:
    Multiplexer(int *, const int);
    void switchOn(int);
    void carouselYellow(int);
    void carouselRed(int);
private:
    int *channels;
    int size;
    const byte truthTable[16][4] = {
        {0,0,0,0},
        {1,0,0,0},
        {0,1,0,0},
        {1,1,0,0},
        {0,0,1,0},
        {1,0,1,0},
        {0,1,1,0},
        {1,1,1,0},
        {0,0,0,1},
        {1,0,0,1},
        {0,1,0,1},
        {1,1,0,1},
        {0,0,1,1},
        {1,0,1,1},
        {0,1,1,1},
        {1,1,1,1}
    };
};

#endif
