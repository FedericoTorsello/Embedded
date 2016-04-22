#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "LedPwm.h"
#include "Context.h"

class LedEnlightingTask: public Task {
public:
  LedEnlightingTask(int pin, Context* pContext);
  void init(int period);
  void tick();
private:
  int pin;
  LightPwm* led;
  Context* pContext;
};

#endif
