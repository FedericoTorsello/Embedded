#include "Button.h"

Button::Button(int pin, unsigned long debounceDelay) {
    this->pin = pin;
    this->debounceDelay = debounceDelay;

    // Variables will change:
    lastButtonState = LOW;   // the previous reading from the input pin
    buttonState = HIGH;
    lastDebounceTime = 0;
    pinMode(pin,INPUT_PULLUP);
}

bool Button::readBool() {

    // sample the state of the button - is it pressed or not?
    buttonState = digitalRead(pin);

    int localTime = millis() - lastDebounceTime;
    //Se abbiamo premuto in pulsante (HIGH) e la volta prima il suo stato
    //era LOW ed è trascorso il tempo necessario
    if(localTime > debounceDelay && buttonState == HIGH && buttonState != lastButtonState) {
            //Inverte l'OUTPUT
            // ledState = !ledState;

            //Ricorda quando l'ultima volta è stato premuto il pulsante
            lastDebounceTime = millis();
    }

    // digitalWrite(ledPin, ledState);  //Scrivo lo stato sul LED
    lastButtonState = !buttonState;

    return lastButtonState;
}
