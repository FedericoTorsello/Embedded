#include "Level.h"
#include "DetectObjTask.h"

int currentLevel;
long currentRandom;


Level::Level(){
}

Level::Level(int initialLevel){
  this->currentLevel = initialLevel;
}

int Level::getLevel(){
  return currentLevel;
}

void Level::setLevel(int value){
  currentLevel = value;
}

long Level::genRndNumber(int min, int max) {
  return random(min,max);
}

void Level::playLevel(int nLevel) {
  setLevel(nLevel);
  printLevel();

  // long rnd = genRndNumber(5,50);
  // if (d >= rnd - 5 && d <= rnd + 5){
  //   pContext->setDetectedObj(d);
  // } else {
  //   pContext->setNoObjDetected();
  // }
}

void Level::printLevel(){
  Serial.println("Livello corrente: " + String(getLevel()));
}
