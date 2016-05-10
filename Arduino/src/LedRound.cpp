#include "LedRound.h"

const int channel[] = {	2, 3, 4, 5 };

LedRound::LedRound(int pin) {
    this->pin = pin;
    pinMode(pin,OUTPUT);
}

void LedRound::switchOn() {
    for (int thisChannel = 0; thisChannel <= 5; thisChannel++) {
        // set the channel pins based on the channel you want:
        // muxWrite(thisChannel);
        for (int thisPin = 0; thisPin <= 3; thisPin++) {
            // calculate the state of this pin based on
            // its bit value in whichChannel:
            int pinState = bitRead(thisChannel, thisPin);
            // turn the pin on or off:
            digitalWrite(channel[thisPin],pinState);
        }
        delay(20);
    }


}

void LedRound::switchOff() {
    digitalWrite(pin,LOW);
}

// void muxWrite(int whichChannel) {
// 	// iterate over the number of pins you're using:
// 	for (int thisPin = 0; thisPin <= 3; thisPin++) {
// 		// calculate the state of this pin based on
// 		// its bit value in whichChannel:
// 		int pinState = bitRead(whichChannel, thisPin);
// 		// turn the pin on or off:
// 		digitalWrite(channel[thisPin],pinState);
// 	}
// }
