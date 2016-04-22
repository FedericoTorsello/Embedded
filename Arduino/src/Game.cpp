#include "Game.h"
// #include "Level.h"

bool stateGame;
// Level level;

Game::Game(){
}

// Game::Game(bool state){
//   this->stateGame = state;
// }

bool Game::isRunning(){
  return stateGame;
}

void Game::startGame(){
  Serial.println("Start Game!");
  stateGame = true;
}

// void Game::startGame(unsigned int setLevel){
//   stateGame = true;
//   level.playLevel(setLevel);
// }

void Game::stopGame(){
  Serial.println("Game Over!");
  stateGame = false;
}
