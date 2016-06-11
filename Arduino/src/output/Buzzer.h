#ifndef __BUZZER__
#define __BUZZER__

#include "../interface/Audio.h"

class Buzzer : public interface::Audio {
public:
    Buzzer(int);
    void playSound(int);
private:
     int NOTE_C4  = 262;
     int NOTE_G3  = 196;

     int NO_NOTE  = 0;
     int NOTE_E6  = 1319;
     int NOTE_G6  = 1568;
     int NOTE_A6  = 1760;
     int NOTE_AS6 = 1865;
     int NOTE_B6  = 1976;
     int NOTE_C7  = 2093;
     int NOTE_D7  = 2349;
     int NOTE_E7  = 2637;
     int NOTE_F7  = 2794;
     int NOTE_G7  = 3136;
     int NOTE_A7  = 3520;

    const int drin[2] = { NOTE_C4, NOTE_G3 };

    const int noteDurations[2] = { 4, 8 };

    // Mario main theme melody
    const int melody2[31] = {
        NOTE_C7, NO_NOTE, NO_NOTE, NOTE_G6,
        NO_NOTE, NO_NOTE, NOTE_E6, NO_NOTE,
        NO_NOTE, NOTE_A6, NO_NOTE, NOTE_B6,
        NO_NOTE, NOTE_AS6, NOTE_A6, NO_NOTE,

        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, NO_NOTE, NOTE_F7, NOTE_G7,
        NO_NOTE, NOTE_E7, NO_NOTE, NOTE_C7,
        NOTE_D7, NOTE_B6, NO_NOTE, NO_NOTE
    };

    void playMarioTheme();
    void buzz(int, int);
    void buzzMarioTheme(unsigned long, unsigned long);
protected:
    int pin;
};
#endif
