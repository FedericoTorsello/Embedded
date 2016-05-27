#ifndef __TASK__
#define __TASK__

class Task {
private:
    int myPeriod;
    int timeElapsed;
    bool enabled;
protected:
    virtual void foo() = 0;
public:
    virtual void init(int, void (*)());

    virtual void init(int period) {
        myPeriod = period;
        timeElapsed = 0;
        enabled = true;
    }
    virtual void tick() = 0;

    void callFoo() {
        foo();
    }

    bool isEnabled() {
        return enabled;
    }
    void enable() {
        enabled = true;
    }
    void disable() {
        enabled = false;
    }

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