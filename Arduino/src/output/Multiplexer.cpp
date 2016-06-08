#include "Multiplexer.h"

Multiplexer::Multiplexer(int *pins, int size) {
    channels = pins;
    this->size = size;

    for (int pin = 0; pin < size; ++pin) {
        pinMode(channels[pin], OUTPUT);
    }
}

// Multiplexer::Multiplexer(int *pins, int size ,int pinInh) {
//     channels = pins;
//     this->size = size;
//     this->pinInh = pinInh;
//     pinMode(pinInh, OUTPUT);
//     digitalWrite(pinInh, LOW);
//
//     for (int pin = 0; pin < size; ++pin) {
//         pinMode(channels[pin], OUTPUT);
//     }
// }

// void Multiplexer::setInh(bool state){
//     digitalWrite(pinInh, state);
// }

void Multiplexer::switchOn(int output) {
    if(output >= 16) {
        Serial.println("Errore: il valore massimo comandabile dal MUX è 16");
    }
    digitalWrite(channels[0], truthTable[output][0]);
    digitalWrite(channels[1], truthTable[output][1]);
    digitalWrite(channels[2], truthTable[output][2]);
    digitalWrite(channels[3], truthTable[output][3]);
}

// void Multiplexer::switchOff() {
// setInh(true);
// }

void Multiplexer::carouselYellow(int del) {
    for (int thisChannel = 0; thisChannel < 6; thisChannel++) {
        // set the channel pins based on the channel you want:
        for (int thisPin = 0; thisPin < 4; thisPin++) {
            // calculate the state of this pin based on
            // its bit value in whichChannel:
            int pinState = bitRead(thisChannel, thisPin);
            // turn the pin on or off:
            digitalWrite(channels[thisPin],pinState);
        }
        delay(del);
    }
}

void Multiplexer::carouselRed(int del) {
    for (int thisChannel = 6; thisChannel < 12; thisChannel++) {
        // set the channel pins based on the channel you want:
        for (int thisPin = 0; thisPin < 4; thisPin++) {
            // calculate the state of this pin based on
            // its bit value in whichChannel:
            int pinState = bitRead(thisChannel, thisPin);
            // turn the pin on or off:
            digitalWrite(channels[thisPin],pinState);
        }
        delay(del);
    }
}
