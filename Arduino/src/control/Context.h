#ifndef __CONTEXT__
#define __CONTEXT__

/*
 * Raccoglie tutti gli stati delle variabili della partita.
 * Viene usato per comunicare tra i vari Task e poter implemantare
 * eventuale busy wait.
 */

class Context {
private:
    bool objDetected;
    float objDistance;
    float maxDistance;
    bool startGame;
    int distanceGuess;

public:
    Context(float maxDistance) {
        objDetected = false;
        this->maxDistance = maxDistance;
    }

    void setDetectedObj(float distance) {
        objDetected = true;
        objDistance = distance;
    }

    void setNoObjDetected() {
        objDetected = false;
    }

    bool isObjDetected() {
        return objDetected;
    }

    float getObjDistance() {
        return objDistance;
    }

    float getMaxDistance() {
        return maxDistance;
    }

    void setGame(bool v) {
        startGame = v;
    }

    bool getGame() {
        return true;
    }

    void setDistanceGuess(int v) {
        distanceGuess = v;
    }

    int getDistanceGuess() {
        return distanceGuess;
    }
};

#endif
