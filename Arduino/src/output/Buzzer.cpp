#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
    this->pin = pin;
    pinMode(pin,OUTPUT);
}

void Buzzer::playSound(int sound) {

    int varDelayValue, varNumCycles;

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
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 2; thisNote++) {
        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];

        int delayValue = (1000000 / melody1[thisNote] / 2) / varDelayValue; // calculate the delay value between transitions
        // 1 second's worth of microseconds, divided by the frequency, then split in half since
        // there are two phases to each cycle
        int numCycles = (melody1[thisNote] * noteDuration / 1000) / varNumCycles; // calculate the number of cycles for proper timing
        // multiply frequency, which is really cycles per second, by the number of seconds to
        // get the total number of cycles to produce

        buzz(numCycles, delayValue);
    }
}


void Buzzer::buzz(int numCycles, int delayValue) {
    for (int i = 0; i < numCycles; i++) {   // for the calculated length of time...
        digitalWrite(pin, HIGH);     // write the buzzer pin high to push out the diaphram
        delayMicroseconds(delayValue);     // wait for the calculated delay value
        digitalWrite(pin, LOW);     // write the buzzer pin low to pull back the diaphram
        delayMicroseconds(delayValue);     // wait again or the calculated delay value
    }
}

void Buzzer::playMarioTheme(){
    // int size = sizeof(melody2) / sizeof(int);
    // for (int thisNote = 0; thisNote < size; thisNote++) {
    for (int thisNote = 0; thisNote < 16; thisNote++) {
        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / 12;

        buzzMarioTheme(melody2[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.3;
        delay(pauseBetweenNotes);
    }
}

void Buzzer::buzzMarioTheme(long frequency, long length) {
    long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
    //// 1 second's worth of microseconds, divided by the frequency, then split in half since
    //// there are two phases to each cycle
    long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
    //// multiply frequency, which is really cycles per second, by the number of seconds to
    //// get the total number of cycles to produce
    for (int i = 0; i < numCycles; i++) { // for the calculated length of time...
        digitalWrite(pin, HIGH); // write the buzzer pin high to push out the diaphram
        delayMicroseconds(delayValue); // wait for the calculated delay value
        digitalWrite(pin, LOW); // write the buzzer pin low to pull back the diaphram
        delayMicroseconds(delayValue); // wait again or the calculated delay value
    }
}
