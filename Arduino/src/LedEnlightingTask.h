#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "LedPwm.h"
#include "Context.h"

class LedEnlightingTask: public Task {

  int pin;
  LightPwm* led;
  Context* pContext;

public:

  LedEnlightingTask(int pin, Context* pContext);
  void init(int period);
  void tick();
};

#endif
