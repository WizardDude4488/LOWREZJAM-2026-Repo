#include <iostream>

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

    begin_game();

    current_game->load_image("black-tile", "black-tile.png");

    current_game->set_tile(0, "black-tile");

    current_game->load_image("white-tile", "white-tile.png");

    current_game->set_tile(1, "white-tile");

    // Create test level
    // Game doesn't handle Level's memory so we need to delete it at application close
    struct TestLevel : public Level {
        void init() override {
            collision_object = nullptr; // Change this with a real level
            player_object = nullptr;

            Tilemap* tilemap = new Tilemap("Tilemap", 0);

            // Create checkerboard pattern
            for (int x = 0; x < TRUE_WIDTH; x++) {
                for (int y = 0; y < TRUE_WIDTH; y++) {
                    if ((x + y) % 2 == 0) {
                        tilemap->set_tile(x, y, 1);
                    }
                    else {
                        tilemap->set_tile(x, y, 0);
                    }
                }
            }

            objects.push_back(tilemap);
        }
    };

    Level* test_level = new TestLevel();

    test_level->init();

    // Do not call delete on tilemap; game handles this automatically

    //current_game->add_object(tilemap);

    // Load level

    current_game->load_level(test_level);

    // Main game loop
    while (!WindowShouldClose()) {
        current_game->draw();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    end_game();

    return 0;
}