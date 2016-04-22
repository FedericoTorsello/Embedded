#include "Scheduler.h"
#include "LedEnlightingTask.h"
#include "DetectObjTask.h"
#include "MsgService.h"
// #include "Button.h"
// #include "Level.h"
#include "Session.h"
#include "Game.h"

Scheduler sched;
Session session;
Game game;
// Led led(13);
// Button button(2);
// Level level;

// unsigned int livelloSelezionato;

void setup() {
    MsgService.init("JimmyChallenge");

    // sched.init(100);
    //Serial.begin(9600); <--questo decommentato fa sballare gli output
    // Context* pContext = new Context(0.5);

    // Task* t0 = new DetectObjTask(8,7,pContext);
    // t0->init(100);
    // sched.addTask(t0);

    // Task* t1 = new LedEnlightingTask(3,pContext);
    // t1->init(100);
    // sched.addTask(t1);

    session.setSession(true);
    if (session.isEnabled()) {
        game.setScore(0);
        //TODO gestiste il feedback
        game.startGame();

        // if (Serial.available()){
        //       livelloSelezionato=  Serial.readString()[0];
        // }
    }

    // questo while è solo un'idea
    // cioè finchè la sessione è true si può giocare
    // (che poi mettendo tutto nel loop() si potrebbe pure far senza)

    // while (session.isEnabled()) {
    //     while (game.isRunning()) {
            // game.playGame(livelloInserito);
        // }


        game.playGame(0);

        if(!game.isRunning()) {
            game.stopGame();
            session.setSession(false);
        }
    // }
}

void loop() {
    // sched.schedule();
    // if (button.readBool()) {
    //   led.switchOn();
    // } else {
    //   led.switchOff();
    // }
}
