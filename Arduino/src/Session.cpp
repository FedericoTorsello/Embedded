#include "Session.h"

unsigned int currentSession;

Session::Session() {
}

Session::Session(int initialSession) {
    this->currentSession = initialSession;
}

int Session::getSession() {
    return currentSession;
}

void Session::setSession(unsigned int value) {
    currentSession = value;
}
