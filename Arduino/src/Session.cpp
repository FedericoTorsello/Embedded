#include "Session.h"
#include "Game.h"

bool currentSession;

Session::Session() {
}

Session::Session(bool initialSession) {
    this->currentSession = initialSession;
}

bool Session::isEnabled() {
    return currentSession;
}

void Session::setSession(bool value) {
    currentSession = value;
}
