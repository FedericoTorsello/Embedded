#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "Task.h"
#include "Context.h"

class GameTask : public Task {
public:
    GameTask(Context* pContext);
    void init(int period);
    void tick();
private:
    Context *pContext;
};

#endif
