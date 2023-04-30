#include <raylib.h>
#include <deque>

class Food
{
private:
	Vector2 position;
	Texture2D texture;
public:
	Food(std::deque<Vector2> snakeBody);
	~Food();

	Vector2 getPosition();
	void setPosition(Vector2 position);

	void Draw();
	Vector2 GenerateRandomCell();
	Vector2 GenerateRandomPosition(std::deque<Vector2> snakeBody);

};

