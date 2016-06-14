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
    if(output <= 16) {
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
    for (int out = 0; out < 6; out++) {
        switchOn(out);
        delay(del);
    }
}

void Multiplexer::carouselRed(int del) {
    for (int out = 6; out < 12; out++) {
        switchOn(out);
        delay(del);
    }
}
