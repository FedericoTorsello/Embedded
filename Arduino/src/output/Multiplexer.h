#ifndef __MULTIPLEXER__
#define __MULTIPLEXER__

#include "Arduino.h"

class Multiplexer {
public:
        Multiplexer(int *, int, int);
        void setInh(bool);
        void switchOn(int);
        void switchOff();
        void carousel(int); 
private:
        int *channels;
        int size;
        int pinInh;
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
