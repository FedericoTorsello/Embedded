#include "GameTask.h"

GameTask::GameTask(Context* pContext) {
    this->pContext = pContext;
}

void GameTask::init(int period) {
    Task::init(period);
}

void GameTask::tick() {

}
