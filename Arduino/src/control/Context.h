#ifndef __CONTEXT__
#define __CONTEXT__

#include "Arduino.h"
#include "../output/Multiplexer.h"

/*
 * Raccoglie tutti gli stati delle variabili della partita.
 * Viene usato per comunicare tra i vari Task e poter implemantare
 * eventuale busy wait.
 */

class Context {
private:
    int maxDistance;
    int currentlevel;
    int randomNum;
    volatile int currentDistance;
    volatile bool gameOver;
    volatile bool buttonPressed;
    volatile bool padlockOpen;
    volatile bool padlockDetected;
    Multiplexer* mux;

public:
    Context(int maxDistance, Multiplexer* mux) {
        this->maxDistance = maxDistance;
        this->mux = mux;
        currentDistance = 0;
        currentlevel = 1;
        randomNum = 0;
        padlockOpen = false;
        padlockDetected = false;
        gameOver = false;

        // utilizzo delle uscite analogiche per creare entropia
        randomSeed(analogRead(A0)*analogRead(A1));
        // mux->switchOn(currentlevel);
    }

    int getMaxDistance(){
        return maxDistance;
    }

    bool isPadlockOpen(){
        return padlockOpen;
    }

    void setPadlockOpen(bool status){
        padlockOpen = status;
    }

    bool isPadlockDetected(){
        return padlockDetected;
    }

    void setPadlockDetected(bool status){
        padlockDetected = status;
    }

    void setCurrentDistance(int lastDistance){
        currentDistance = lastDistance;
    }

    int getCurrentDistance(){
        return currentDistance;
    }

    void setButtonPressed(bool buttonState){
        buttonPressed = buttonState;
    }

    bool isButtonPressed(){
        return buttonPressed;
    }

    void setLevelToPlay(int nLevel){
        newRandomNumber();
        currentlevel = nLevel + 1;
    }

    int getLevelToPlay(){
        return currentlevel;
    }

    int getRandomNumber(){
        return randomNum;
    }

    void newRandomNumber(){
        randomNum = random(5, maxDistance);
    }

    void setGameOver(bool gameState){
        gameOver = gameState;
        mux->carouselRed(100);
        mux->carouselYellow(100);
    }

    bool isGameOver(){
        return gameOver;
    }

};

#endif
