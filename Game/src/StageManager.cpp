#include "../include/StageManager.h"

namespace gnGame {

    StageManager* StageManager::getIns()
    {
        static StageManager Instance;
        return &Instance;
    }

    int StageManager::getUnlockCurrentStage()
    {
        return UnlockCurrentStage;
    }

    void StageManager::unlockStage()
    {
        if (UnlockCurrentStage >= MAXSTAGE - 1) {
            return;
        }

        UnlockCurrentStage++;
    }

    int StageManager::getCurrentStage()
    {
        return currentStage;
    }

    void StageManager::incrementCurrentStage()
    {
        if (currentStage >= UnlockCurrentStage) {
            return;
        }

        ++StageManager::currentStage;
    }

    void StageManager::decrementCurrentStage()
    {
        if (currentStage <= 0) {
            return;
        }

        --StageManager::currentStage;
    }
}
