#ifndef __BUZZER__
#define __BUZZER__

#include "../interface/Audio.h"

class Buzzer : public interface::Audio {
public:
    Buzzer(int);
    void playSound(int);
private:
    const int NOTE_C4  = 262;
    const int NOTE_G3  = 196;

    const uint16_t NO_NOTE  = 0;
    const uint16_t NOTE_E6  = 1319;
    const uint16_t NOTE_G6  = 1568;
    const uint16_t NOTE_A6  = 1760;
    const uint16_t NOTE_AS6 = 1865;
    const uint16_t NOTE_B6  = 1976;
    const uint16_t NOTE_C7  = 2093;
    const uint16_t NOTE_D7  = 2349;
    const uint16_t NOTE_E7  = 2637;
    const uint16_t NOTE_F7  = 2794;
    const uint16_t NOTE_G7  = 3136;
    const uint16_t NOTE_A7  = 3520;

    const int melody1[2] = {
        NOTE_C4, NOTE_G3
    };

    // Mario main theme melody
    const uint16_t melody2[31] = {
        NOTE_C7, NO_NOTE, NO_NOTE, NOTE_G6,
        NO_NOTE, NO_NOTE, NOTE_E6, NO_NOTE,
        NO_NOTE, NOTE_A6, NO_NOTE, NOTE_B6,
        NO_NOTE, NOTE_AS6, NOTE_A6, NO_NOTE,

        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, NO_NOTE, NOTE_F7, NOTE_G7,
        NO_NOTE, NOTE_E7, NO_NOTE, NOTE_C7,
        NOTE_D7, NOTE_B6, NO_NOTE, NO_NOTE
    };

    const uint8_t noteDurations[2] = { 4, 8 };

    void playMarioTheme();
    void buzz(int, int);
    void buzzMarioTheme(long, long);
protected:
    int pin;
};
#endif
