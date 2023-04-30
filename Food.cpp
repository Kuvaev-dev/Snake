#include "Food.h"
#include "GameManager.h"
#include "GameParameters.h"

Food::Food(std::deque<Vector2> snakeBody) {
	Image image = LoadImage(foodImagePath);
	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	position = GenerateRandomPosition(snakeBody);
}

Food::~Food() {
	UnloadTexture(texture);
}

Vector2 Food::getPosition()
{
	return this->position;
}

void Food::setPosition(Vector2 position)
{
	this->position = position;
}

void Food::Draw() {
	DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell() {
	float x = GetRandomValue(0, cellCount - 1);
	float y = GetRandomValue(0, cellCount - 1);

	return Vector2{ x, y };
}

Vector2 Food::GenerateRandomPosition(std::deque<Vector2> snakeBody) {
	GameManager gm;
	Vector2 position = GenerateRandomCell();

	while (gm.ElementInDeque(position, snakeBody)) {
		position = GenerateRandomCell();
	}

	return position;
}