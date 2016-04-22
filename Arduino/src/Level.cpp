#include "Level.h"
#include "DetectObjTask.h"

unsigned int currentLevel;
long currentRandom;


Level::Level() {
}

Level::Level(unsigned int initialLevel) {
    this->currentLevel = initialLevel;
}

unsigned int Level::getLevel() {
    return currentLevel;
}

void Level::printLevel() {
    Serial.println("Current level " + String(getLevel()));
}

void Level::setLevel(unsigned int value) {
    currentLevel = value;
}

long Level::genRndNumber(unsigned int min, unsigned int max) {
    return random(min,max);
}

void Level::playLevel(unsigned int nLevel) {
    setLevel(nLevel);
    printLevel();


    // long rnd = genRndNumber(5,50);
    // if (d >= rnd - 5 && d <= rnd + 5){
    //   pContext->setDetectedObj(d);
    // } else {
    //   pContext->setNoObjDetected();
    // }
}
