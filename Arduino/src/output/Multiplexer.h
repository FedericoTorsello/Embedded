#ifndef __MULTIPLEXER__
#define __MULTIPLEXER__

#include "Arduino.h"

class Multiplexer {
public:
    Multiplexer(int *, int);
    void switchOn(int);
    void carousel(int);
private:
    int *channels;
    int size;
    byte truthTable[16][4] = {
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
