#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>

using namespace std;

Color green = { 173, 204, 96, 255 };    // RGBA
Color darkGreen = { 43, 51, 24, 255 };

float cellSize = 25.;
int cellCount = 25;
float offset = 75.;

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 element, deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque.at(i), element)) {
            return true;
        }
    }
    return false;
}

class Snake {
public:
    deque<Vector2> body = {
        Vector2 { 6, 9 },
        Vector2 { 5, 9 },
        Vector2 { 4, 9 }
    };
    Vector2 direction = { 1, 0 };
    bool addSegment = false;

    void Draw() {
        for (unsigned int i = 0; i < body.size(); i++) {
            float x = body.at(i).x;
            float y = body.at(i).y;
            Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize,cellSize,cellSize };
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update() {
        body.push_front(Vector2Add(body.at(0), direction));

        if (addSegment == true) {
            addSegment = false;
        } else {
            body.pop_back();
        }
    }

    void Reset() {
        body = {
            Vector2 { 6, 9 },
            Vector2 { 5, 9 },
            Vector2 { 4, 9 }
        };
        direction = { 1, 0 };
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody) {
        Image image = LoadImage("assets/graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPosition(snakeBody);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);

        return Vector2{ x, y };
    }

    Vector2 GenerateRandomPosition(deque<Vector2> snakeBody) {
        Vector2 position = GenerateRandomCell();

        while (ElementInDeque(position, snakeBody)) {
            position = GenerateRandomCell();
        }

        return position;
    }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game() {
        InitAudioDevice();
        eatSound = LoadSound("assets/sounds/eat.mp3");
        wallSound = LoadSound("assets/sounds/wall.mp3");
    }

    ~Game() {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        if (running) {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood() {
        if (Vector2Equals(snake.body.at(0), food.position)) {
            food.position = food.GenerateRandomPosition(snake.body);
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges() {
        if (snake.body.at(0).x == cellCount || snake.body.at(0).x == -1) {
            GameOver();
        }

        if (snake.body.at(0).y == cellCount || snake.body.at(0).y == -1) {
            GameOver();
        }
    }

    void GameOver() {
        snake.Reset();
        food.position = food.GenerateRandomPosition(snake.body);
        running = false;
        score = 0;
        ::PlaySound(wallSound);
    }

    void CheckCollisionWithTail() {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();

        if (ElementInDeque(snake.body.at(0), headlessBody)) {
            GameOver();
        }
    }
};

int main() {
    cout << "Start...";
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake | Kuvaiev Mykyta");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false) {
        BeginDrawing();

        if (EventTriggered(0.2)) {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = { 0, -1 };
            game.running = true;
        } else if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = { 0, 1 };
            game.running = true;
        } else if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = { -1, 0 };
            game.running = true;
        } else if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = { 1, 0 };
            game.running = true;
        }

        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{ offset - 5, offset - 5, cellSize * cellCount + 10, cellSize * cellCount + 10 }, 5, darkGreen);
        DrawText("Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}