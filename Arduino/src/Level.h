#include "Arduino.h"

#ifndef __LEVEL__
#define __LEVEL__


class Level {
public:
  Level();
  Level(unsigned int initialLevel);
  unsigned int getLevel();
  void setLevel(unsigned int value);
  long genRndNumber(unsigned int min, unsigned int max);
  void playLevel(unsigned int nLevel);
  void printLevel();
private:
  unsigned int currentLevel;
  long currentRandom;
};

#endif
