#include "Session.h"

int currentSession;

Session::Session(){
}

Session::Session(int initialSession){
  this->currentSession = initialSession;
}

int Session::getSession(){
  return currentSession;
}

void Session::setSession(int value){
  currentSession = value;
}
