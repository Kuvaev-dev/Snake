#include "Game.h"
#include "GameManager.h"
#include "GameParameters.h"

Game::Game() {
	InitAudioDevice();
	eatSound = LoadSound(eatSoundPath);
	wallSound = LoadSound(wallSoundPath);
}

Game::~Game() {
	UnloadSound(eatSound);
	UnloadSound(wallSound);
	CloseAudioDevice();
}

Snake& Game::getSnake() {
	return this->snake;
}

void Game::setRunning(bool running) {
	this->running = running;
}

int Game::getScore() {
	return this->score;
}

void Game::Draw() {
	this->food.Draw();
	this->snake.Draw();
}

void Game::Update() {
	if (this->running) {
		this->snake.Update();
		CheckCollisionWithFood();
		CheckCollisionWithEdges();
		CheckCollisionWithTail();
	}
}

void Game::CheckCollisionWithFood() {
	if (Vector2Equals(this->snake.getBody().at(0), this->food.getPosition())) {
		this->food.setPosition(this->food.GenerateRandomPosition(this->snake.getBody()));
		this->snake.setSegment(true);
		this->score++;
		PlaySound(eatSound);
	}
}

void Game::CheckCollisionWithEdges() {
	if (this->snake.getBody().at(0).x == cellCount || this->snake.getBody().at(0).x == -1) {
		GameOver();
	}

	if (this->snake.getBody().at(0).y == cellCount || this->snake.getBody().at(0).y == -1) {
		GameOver();
	}
}

void Game::GameOver() {
	this->snake.Reset();
	this->food.setPosition(this->food.GenerateRandomPosition(this->snake.getBody()));
	this->running = false;
	this->score = 0;
	PlaySound(wallSound);
}

void Game::CheckCollisionWithTail() {
	GameManager gm;
	std::deque<Vector2> headlessBody = this->snake.getBody();
	headlessBody.pop_front();

	if (gm.ElementInDeque(this->snake.getBody().at(0), headlessBody)) {
		GameOver();
	}
}