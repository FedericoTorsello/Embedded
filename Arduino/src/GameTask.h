#ifndef __BUTTONTASK__
#define __BUTTONTASK__

#include "Task.h"
#include "Context.h"

class GameTask : public Task {
public:
    GameTask(Context *);
    void init(int);
    void tick();
private:
    Context *pContext;
};

#endif
