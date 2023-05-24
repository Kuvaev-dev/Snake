#include "Snake.h"

std::deque<Vector2> Snake::getBody() { return this->body; }

float Snake::getXDirection() { return this->direction.x; }

float Snake::getYDirection() { return this->direction.y; }

void Snake::setDirection(float x, float y) { this->direction = { x, y }; }

bool Snake::getSegment() { return this->addSegment; }

void Snake::setSegment(bool addSegment) { this->addSegment = addSegment; }

void Snake::Draw() {
	for (unsigned int i = 0; i < this->body.size(); i++) {
		float x = this->body.at(i).x;
		float y = this->body.at(i).y;
		Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize,cellSize,cellSize };
		DrawRectangleRounded(segment, 0.5, 6, darkGreen);
	}
}

void Snake::Update() {
	this->body.push_front(Vector2Add(this->body.at(0), direction));

	if (this->addSegment == true) {
		this->addSegment = false;
	} else {
		this->body.pop_back();
	}
}

void Snake::Reset() {
	this->body = {
		Vector2 { 6, 9 },
		Vector2 { 5, 9 },
		Vector2 { 4, 9 }
	};
	this->direction = { 1, 0 };
}