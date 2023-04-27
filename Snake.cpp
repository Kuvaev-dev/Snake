#include <iostream>
#include <raylib.h>

using namespace std;

int main() {
    const int GAME_WINDOW_WIDTH = 750, GAME_WINDOW_HEIGHT = 750;
    cout << "Start...";
    InitWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, "Snake | Kuvaiev Mykyta");
    system("pause");
    return 0;
}