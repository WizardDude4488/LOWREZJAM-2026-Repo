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

    game->load_image("white-tile", "white-tile.png");

    game->set_tile(1, "white-tile");

    Tilemap* tilemap = new Tilemap("Tilemap", 0);

    for (int x = 0; x <= TRUE_WIDTH; x++) {
        for (int y = 0; y <= TRUE_WIDTH; y++) {
            if ((x + y) % 2 == 0) {
                tilemap->set_tile(x, y, 1);
            }
        }
    }

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