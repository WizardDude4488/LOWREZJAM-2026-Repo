#include <iostream>
#include <string>

#include "raylib.h"

#include "Game.hpp"
#include "Tilemap.hpp"
#include "Helper.hpp"
#include "Load.hpp"
#include "monsters/Crab.hpp"
#include "monsters/Seagull.hpp"
#include "monsters/Bullet.hpp"
#include "monsters/Pirate.hpp"

int main(void) {
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    begin_game();

    /*current_game->load_image("black-tile", "black-tile.png");

    current_game->set_tile(0, "black-tile");

    current_game->load_image("white-tile", "white-tile.png");

    current_game->set_tile(1, "white-tile");*/

    load_assets();

    current_game->load_image("bullet", "bullet.png");

    current_game->load_image("bullet", "bullet.png");

    // HERE
    // Game hangs right here

    // Create test level
    // Game doesn't handle Level's memory so we need to delete it at application close
    struct TestLevel : public Level {
        void init() override {

            const std::vector<int>& wall_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                  -1, 0, 20, 40, 40, 40, 40, 60, 80, -1,
                                                  -1, 1, -1, -1, -1, -1, -1, -1, 81, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 3, -1, -1, -1, -1, -1, -1, 83, -1,
                                                  -1, 4, 24, 44, 44, 44, 44, 64, 84, -1,
                                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            const std::vector<int>& floor_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, 21, 41, 41, 41, 41, 61, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 23, 43, 43, 43, 43, 63, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            collision_object = new Tilemap("Walls", 1, wall_data);

            // Give player and crab different positions

            player_object = new Player("Bob", { 32.0f, 32.0f });

            Tilemap* tilemap = new Tilemap("Floor", 0, floor_data);

            //Crab* crab_object = new Crab("Krabs", { 16.0f, 16.0f }, { 48.0f, 16.0f }, 30.0f);

            //Bullet* bullet_object = new Bullet("Bullet", { 16.0f, 16.0f }, {0.0f, 1.0f}, 15.0f);

            //Seagull* seagull_object = new Seagull("Seagull", {40.0f, 40.0f}, 50.0f);

            Pirate* pirate_object = new Pirate("Pirate", { 40.0f, 40.0f }, 50.0f);

            // Make border around map; Remember that there is an extra block border around the screen

            collision_object->set_square(0, 0, TRUE_WIDTH - 1, TRUE_WIDTH - 1, 0);

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(tilemap);
            //objects.push_back(crab_object);
            //objects.push_back(seagull_object);
            //objects.push_back(bullet_object);
            objects.push_back(pirate_object);
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
        current_game->empty_queue();
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