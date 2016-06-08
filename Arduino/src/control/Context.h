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
    int dangerLevel;
    bool statoDiScasso;
    volatile int currentDistance;
    volatile bool gameOver;
    volatile bool buttonPressed;
    volatile bool padlockOpen;
    volatile bool padlockDetected;

    Multiplexer* mux;
    String from;
    String to;

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
        statoDiScasso = false;
        from = "";
        to = "";
        dangerLevel = 0;
        mux->switchOn(currentlevel);

        // utilizzo delle uscite analogiche per creare entropia
        randomSeed(analogRead(A0));
    }

    bool isPadlockOpen(){
        return padlockOpen;
    }

    void setPadlockOpen(bool padlockOpen){
        this->padlockOpen = padlockOpen;
    }

    bool isPadlockDetected(){
        return padlockDetected;
    }

    void setPadlockDetected(bool padlockDetected){
        this->padlockDetected = padlockDetected;
    }

    void setCurrentDistance(int currentDistance){
        this->currentDistance = currentDistance;
    }

    int getCurrentDistance(){
        return currentDistance;
    }

    void setButtonPressed(bool buttonPressed){
        this->buttonPressed = buttonPressed;
    }

    bool isButtonPressed(){
        return buttonPressed;
    }

    void setLevelToPlay(int currentlevel){
        newRandomNumber();
        this->currentlevel = currentlevel + 1;
        mux->switchOn(this->currentlevel);
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

    void setGameOver(bool gameOver){
        this->gameOver = gameOver;
    }

    bool isGameOver(){
        return gameOver;
    }

    void setFrom(String from) {
        this->from = from;
    }

    String getFrom(){
        return from;
    }

    void setTo(String to) {
        this->to = to;
    }

    String getTo(){
        return to;
    }

    void setDangerLevel(int dangerLevel){
        this->dangerLevel = dangerLevel;
    }

    int getDangerLevel(){
        return dangerLevel;
    }

    void setStatoDiScasso(bool statoDiScasso){
        this->statoDiScasso = statoDiScasso;
    }

    bool isStatoDiScasso(){
        return statoDiScasso;
    }

    void carousel(int delay1, int delay2){
        mux->carouselRed(delay1);
        mux->carouselYellow(delay2);
    }
};

#endif
