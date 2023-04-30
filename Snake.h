#include "GameParameters.h"
#include <deque>

class Snake
{
private:
    std::deque<Vector2> body = {
        Vector2 { 6, 9 },
        Vector2 { 5, 9 },
        Vector2 { 4, 9 }
    };
    bool addSegment = false;
    Vector2 direction = { 1, 0 };
public:
    std::deque<Vector2> getBody();
    Vector2 getDirection();
    void setDirection(float x, float y);
    bool getSegment();
    void setSegment(bool addSegment);

    void Draw();
    void Update();
    void Reset();
};

