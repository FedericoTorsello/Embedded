#ifndef __CONTEXT__
#define __CONTEXT__

/*
 * Raccoglie tutti gli stati delle variabili della partita.
 * Viene usato per comunicare tra i vari Task e poter implemantare
 * eventuale busy wait.
 */

class Context {
private:
    int maxDistance;
    bool padlockOpen;
    bool padlockDetected;
    int currentDistance;
    bool buttonPressed;
public:
    Context(int maxDistance) {
        this->maxDistance = maxDistance;
        padlockOpen = false;
        padlockDetected = false;
        currentDistance = 0;
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


};

#endif
