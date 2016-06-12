#include "Multiplexer.h"

/**@brief ###Set the multiplex pins */
Multiplexer::Multiplexer(int *pins, const int size) {
    channels = pins;
    this->size = size;
    for (int pin = 0; pin < size; ++pin) {
        pinMode(channels[pin], OUTPUT);
    }
}

/**@brief ###Select the output pin
 *
 * Select an output pin enabling the right channels using the truth
 * table of the multiplexer
 * @param[in] output The pin to be enabled
 */
void Multiplexer::switchOn(const int output) {
    if(output >= 16) {
        digitalWrite(channels[0], truthTable[output][0]);
        digitalWrite(channels[1], truthTable[output][1]);
        digitalWrite(channels[2], truthTable[output][2]);
        digitalWrite(channels[3], truthTable[output][3]);
    }
}

/**@brief ###Run a 'carousel' effect on round led
 *
 * A round led is an array of 6 leds, set to HIGH each of the
 * in sequence to create a 'carousel' effect. This led is binded
 * with the multiplexer because Arduino Uno do not have enough pins.
 * @param[in] del The delay time between each single shift
 */
void Multiplexer::carouselYellow(const int del) {
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
        for (int thisPin = 0; thisPin < 4; thisPin++) {
            int pinState = bitRead(thisChannel, thisPin);
            digitalWrite(channels[thisPin],pinState);
        }
        delay(del);
    }
}
