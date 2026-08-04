#include <iostream>

#include "raylib.h"

#include "Game.hpp"
#include "Tilemap.hpp"
#include "monsters/Crab.hpp"
#include "monsters/Seagull.hpp"
#include "monsters/Bullet.hpp"

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

    current_game->load_image("yellow-guy", "yellow-guy.png");

    current_game->load_image("crab", "crab.png");

    current_game->load_image("seagull", "seagull.png");

    current_game->load_image("bullet", "bullet.png");

    // HERE
    // Game hangs right here

    // Create test level
    // Game doesn't handle Level's memory so we need to delete it at application close
    struct TestLevel : public Level {
        void init() override {
            collision_object = new Tilemap("Walls", 1);

            // Give player and crab different positions

            player_object = new Player("Bob", { 32.0f, 32.0f });

            Tilemap* tilemap = new Tilemap("Floor", 0);

            Crab* crab_object = new Crab("Krabs", { 16.0f, 16.0f }, { 48.0f, 16.0f }, 30.0f);

            Bullet* bullet_object = new Bullet("Bullet", { 16.0f, 16.0f }, {0.0f, 1.0f}, 15.0f);

            Seagull* seagull_object = new Seagull("Seagull", {40.0f, 40.0f}, 50.0f);

            // Fill with white tile
            for (int x = 0; x < TRUE_WIDTH; x++) {
                for (int y = 0; y < TRUE_WIDTH; y++) {
                    tilemap->set_tile(x, y, 1);
                }
            }

            // Make border around map; Remember that there is an extra block border around the screen

            collision_object->set_square(0, 0, TRUE_WIDTH - 1, TRUE_WIDTH - 1, 0);
            collision_object->set_square(1, 1, TRUE_WIDTH - 2, TRUE_WIDTH - 2, 0);

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(tilemap);
            objects.push_back(crab_object);
            objects.push_back(seagull_object);
            objects.push_back(bullet_object);
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
        current_game->update();
        current_game->draw();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // TODO: game seg-faults when closing, determine cause
    // (something to do with clearing textures)

    end_game();
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}