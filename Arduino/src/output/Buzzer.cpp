#include "Buzzer.h"

/** @brief ###Set the buzzer */
Buzzer::Buzzer(const int pin) {
    this->pin = pin;
    pinMode(pin,OUTPUT);
}

/** @brief ###Play a sound
 *
 * Choose wich sound to play
 * @param[in] sound The sound to play
 */
void Buzzer::playSound(const int sound) {
    int varDelayValue = 0, varNumCycles = 0;

    switch (sound) {
    case 0:
        varDelayValue = 2;
        varNumCycles = 2;
        break;
    case 1:
        varDelayValue = 3;
        varNumCycles = 1;
        break;
    case 2:
        playMarioTheme();
        break;
    default:
        varDelayValue = 1;
        varNumCycles = 1;
        break;
    }
    for (int thisNote = 0; thisNote < 2; thisNote++) {
        // To calculate the note duration, take one second divided by the note type.
        int noteDuration = 1000 / noteDurations[thisNote];
        // Calculate the delay value between transitions
        // 1 second's worth of microseconds, divided by the frequency, then split in half since there are two phases to each cycle
        int delayValue = (1000000 / drin[thisNote] / 2) / varDelayValue;
        // Calculate the number of cycles for proper timing
        // Multiply frequency, which is really cycles per second, by the number of seconds to
        // get the total number of cycles to produce
        int numCycles = (drin[thisNote] * noteDuration / 1000) / varNumCycles;
        buzz(numCycles, delayValue);
    }
}

/** @brief ###Play a note setting the pin HIGH or LOW
 *
 * Play a note setting the pin HIGH or LOW using delay for some time
 * @param[int] numCycles The calculated lenght of time
 * @param[int] delayValue The delay time calculated
 */
void Buzzer::buzz(int numCycles, int delayValue) {
    for (int i = 0; i < numCycles; i++) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(delayValue);
        digitalWrite(pin, LOW);
        delayMicroseconds(delayValue);
    }
}

/** @brief ###Play the Super Mario theme song
 *
 * This function computes, for each note, the delay and the frequency
 * to play the famous Super Mario theme song
 */
void Buzzer::playMarioTheme() {
    int size = sizeof(melody2) / sizeof(int);
    for (uint8_t thisNote = 0; thisNote < size; thisNote++) {
        uint8_t noteDuration = 1000 / 12;
        long frequency = melody2[thisNote];
        long delayValue = 1000000 / frequency / 2;
        int numCycles = frequency * noteDuration / 1000;
        // Play one note
        buzz(numCycles, delayValue);
        // To distinguish the notes, set a minimum time between them. (~30%)
        uint8_t pauseBetweenNotes = noteDuration * 1.3;
        delay(pauseBetweenNotes);
    }
}
