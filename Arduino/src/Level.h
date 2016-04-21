#include "Arduino.h"

#ifndef __LEVEL__
#define __LEVEL__


class Level {

  int currentLevel;
  long currentRandom;

public:
  Level();
  Level(int initialLevel);
  int getLevel();
  void setLevel(int value);
  long genRndNumber(int min, int max);
  void playLevel(int nLevel);
  void printLevel();
};

#endif
