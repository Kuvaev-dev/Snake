#include "GameParameters.h"
#include <raylib.h>
#include <raymath.h>
#include <deque>

class GameManager
{
public:
	bool EventTriggered(double interval);
	bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);
};

