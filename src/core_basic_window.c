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
        game_handle_inputs(&game);
        game_update(&game, GetFrameTime(), GetTime());
        BeginDrawing();
            ClearBackground(BROWN);
            DrawFPS(0, 0);
            game_draw(&game);
        EndDrawing();
    }

    game_shutdown(&game);
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
