#ifndef __DETECTOBJTASK__
#define __DETECTOBJTASK__

#include "Task.h"
#include "Context.h"

class DetectObjTask: public Task {
public:
  DetectObjTask(int trigPin, int echoPin, Context* pContext);
  void init(int period);
  void tick();
private:
  Context* pContext;
  int echoPin;
  int trigPin;
};

#endif
