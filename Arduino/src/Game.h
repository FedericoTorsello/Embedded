#ifndef __GAME__
#define __GAME__

#include "Arduino.h"


class Game {
public:
    Game();
    // Game(bool state);

    bool isRunning();
    void startGame();
    // void startGame(unsigned int setLevel);
    void stopGame();
private:
    bool stateGame;
};

#endif
