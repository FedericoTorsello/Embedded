#ifndef __TASK__
#define __TASK__

class Task {
private:
    int myPeriod;
    int timeElapsed;
    bool enabled;
public:
    bool isEnabled() { return enabled; }
    void enable() { enabled = true; }
    void disable() { enabled = false; }

    virtual void init(int period) {
        myPeriod = period;
        timeElapsed = 0;
        enabled = true;
    }
    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }

};

#endif
