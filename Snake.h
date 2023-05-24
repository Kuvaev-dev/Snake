#include "GameParameters.h"
#include "GameObject.h"
#include <deque>

class Snake : public GameObject
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
    float getXDirection();
    float getYDirection();
    void setDirection(float x, float y);
    bool getSegment();
    void setSegment(bool addSegment);

    void Draw() override;
    void Update() override;
    void Reset();
};

