#include "Game.hpp"
#include "Tilemap.hpp"

#include "raylib.h"

int main(void) {
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Game* game = new Game();

    game->load_image("black-tile", "black-tile.png");

    game->set_tile(0, "black-tile");

    Tilemap* tilemap = new Tilemap("Tilemap", 0);

    // Do not call delete on tilemap; game handles this automatically

    game->add_object(tilemap);

    // Main game loop
    while (!WindowShouldClose()) {
        game->draw();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    delete game;

    return 0;
}