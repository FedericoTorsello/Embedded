#include "Game.h"
#include "Level.h"

bool stateGame;
unsigned int score;
Level level;

Game::Game() {
}

// Game::Game(bool state){
//   this->stateGame = state;
// }

bool Game::isRunning() {
    return stateGame;
}

void Game::startGame() {
    Serial.println("Start Game!");
    stateGame = true;
}

void Game::stopGame() {
    Serial.println("Game Over!");
    stateGame = false;
}

void Game::setScore(unsigned int newScore){
    score = newScore;
}

void Game::playGame(unsigned int selectLevel){
    switch (selectLevel) {
        case 0:
            level.playLevel(0);
            break;
        case 1:
            level.playLevel(1);
            break;
        case 2:
            level.playLevel(2);
            break;
        case 3:
            level.playLevel(3);
            break;
        default:;
    }
}
