#ifndef __DETECTOBJTASK__
#define __DETECTOBJTASK__

#include "Task.h"
#include "Context.h"

class DetectObjTask: public Task {

  Context* pContext;
  int echoPin;
  int trigPin;

public:

  DetectObjTask(int trigPin, int echoPin, Context* pContext);
  void init(int period);
  void tick();
};

#endif
