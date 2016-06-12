#ifndef __TASK__
#define __TASK__

/** Abstract class for tasks */
class Task {
private:
    int period;                         /**< Execution Time */
    int timeElapsed;                    /**< Time of execution */
    bool enabled;                       /**< If the task is enabled */
protected:
    virtual void lambdaTick() = 0;      /**< The implementation of task */
public:
    virtual void init(int period) {
        this->period = period;
        timeElapsed = 0;
        enabled = true;
    }
    virtual void tick() = 0;

    bool isEnabled() {
        return enabled;
    }

    void enable() {
        enabled = true;
    }
    void disable() {
        enabled = false;
    }

    /**@brief ###Check if is time to do a context switch
     *
     * @param[in] basePeriod The period time of execution of the task
     */
    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if (timeElapsed >= period) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }
};

#endif
