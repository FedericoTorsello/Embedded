#ifndef __BUZZER__
#define __BUZZER__

#include "../interface/Audio.h"

class Buzzer : public interface::Audio {
public:
    Buzzer(int);
    void playSound(int);
    void stopSound();

protected:
    int pin;
private:
    const int NOTE_C4 = 262;
    const int NOTE_G3 = 196;
    const int melody1[2] = {
        NOTE_C4, NOTE_G3
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    const int noteDurations[2] = {
        4, 8
    };

    void buzz(int, int);
};
#endif
