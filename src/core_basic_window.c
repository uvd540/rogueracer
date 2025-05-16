#include "game.h"
#include "raylib.h"

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "rogueracer");
    Game game = {0};
    game_init(&game);

    SetTargetFPS(60);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game_update(&game, GetFrameTime());
        BeginDrawing();
            ClearBackground(BROWN);
            game_draw(&game);
        EndDrawing();
    }

    game_shutdown(&game);
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
