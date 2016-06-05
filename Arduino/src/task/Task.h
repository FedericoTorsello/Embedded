#ifndef __TASK__
#define __TASK__

class Task {
public:
    virtual void init(int period) {
        this->period = period;
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
        if (timeElapsed >= period) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }
private:
    int period;
    int timeElapsed;
    bool enabled;
protected:
    virtual void foo() = 0;
};

#endif
