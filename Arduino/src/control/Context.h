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

    int getCurrentDistance(){
        return currentDistance;
    }


};

#endif
