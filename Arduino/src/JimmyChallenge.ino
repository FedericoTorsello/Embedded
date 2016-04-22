#include "Scheduler.h"
#include "LedEnlightingTask.h"
#include "DetectObjTask.h"
#include "MsgService.h"
// #include "Button.h"
// #include "Level.h"
#include "Session.h"
#include "Game.h"
#include "Level.h"

Scheduler sched;
Session session;
Game game;
Level level;
// Led led(13);
// Button button(2);
// Level level;

void setup(){
  MsgService.init("JimmyChallenge");

  // sched.init(100);
  // Serial.begin(9600);
  // Context* pContext = new Context(0.5);
  //
  // Task* t0 = new DetectObjTask(8,7,pContext);
  // t0->init(100);
  // sched.addTask(t0);
  //
  // Task* t1 = new LedEnlightingTask(3,pContext);
  // t1->init(100);
  // sched.addTask(t1);

  session.setSession(1);

  if(session.getSession() != 0){
      game.startGame();
  }

  if(game.isRunning()){
    level.setLevel(0);
    level.playLevel(level.getLevel());
  }else{
    game.stopGame();
  }

}

void loop(){
  // sched.schedule();
  // if(button.readBool()){
  //   led.switchOn();
  // }else{
  //   led.switchOff();
  // }
}
