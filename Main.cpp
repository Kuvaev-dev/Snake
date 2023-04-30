#include "GameManager.h"
#include "GameParameters.h"
#include "Game.h"

using namespace std;

Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };
float cellSize = 25.;
int cellCount = 25;
double lastUpdateTime = 0;
float offset = 75.;
const char* eatSoundPath = "assets/sounds/eat.mp3";
const char* wallSoundPath = "assets/sounds/wall.mp3";
const char* foodImagePath = "assets/graphics/food.png";

int main() {
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake | Kuvaiev Mykyta");
    SetTargetFPS(60);

    GameManager gm;
    Game game;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        if (gm.EventTriggered(0.2)) {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.getSnake().getDirection().y != 1) {
            game.getSnake().setDirection(0, -1);
            game.setRunning(true);
        }
        else if (IsKeyPressed(KEY_DOWN) && game.getSnake().getDirection().y != -1) {
            game.getSnake().setDirection(0, 1);
            game.setRunning(true);
        }
        else if (IsKeyPressed(KEY_LEFT) && game.getSnake().getDirection().x != 1) {
            game.getSnake().setDirection(-1, 0);
            game.setRunning(true);
        }
        else if (IsKeyPressed(KEY_RIGHT) && game.getSnake().getDirection().x != -1) {
            game.getSnake().setDirection(1, 0);
            game.setRunning(true);
        }

        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{ offset - 5, offset - 5, cellSize * cellCount + 10, cellSize * cellCount + 10 }, 5, darkGreen);
        DrawText("Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.getScore()), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}