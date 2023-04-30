#include "Snake.h"

std::deque<Vector2> Snake::getBody()
{
	return this->body;
}

Vector2 Snake::getDirection()
{
	return this->direction;
}

void Snake::setDirection(float x, float y)
{
	this->direction = { x, y };
}

bool Snake::getSegment()
{
	return this->addSegment;
}

void Snake::setSegment(bool addSegment)
{
	this->addSegment = addSegment;
}

void Snake::Draw() {
	for (unsigned int i = 0; i < body.size(); i++) {
		float x = body.at(i).x;
		float y = body.at(i).y;
		Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize,cellSize,cellSize };
		DrawRectangleRounded(segment, 0.5, 6, darkGreen);
	}
}

void Snake::Update() {
	body.push_front(Vector2Add(body.at(0), direction));

	if (addSegment == true) {
		addSegment = false;
	}
	else {
		body.pop_back();
	}
}

void Snake::Reset() {
	body = {
		Vector2 { 6, 9 },
		Vector2 { 5, 9 },
		Vector2 { 4, 9 }
	};
	direction = { 1, 0 };
}