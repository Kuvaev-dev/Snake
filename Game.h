#include "Snake.h"
#include "Food.h"
#include <deque>

class Game
{
private:
    Snake snake = Snake();
    Food food = Food(snake.getBody());
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;
public:
    Game();
    ~Game();

    Snake& getSnake();
    void setRunning(bool running);
    int getScore();

    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
    void GameOver();
};

