#include "GameManager.h"

bool GameManager::EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool GameManager::ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque.at(i), element)) {
            return true;
        }
    }
    return false;
}
