#include <iostream>
#include <string>

#include "raylib.h"

#include "Game.hpp"
#include "Door.hpp"
#include "Tilemap.hpp"
#include "Helper.hpp"
#include "Load.hpp"
#include "monsters/Crab.hpp"
#include "monsters/Seagull.hpp"
#include "monsters/Bullet.hpp"
#include "monsters/Pirate.hpp"
#include "weapons/RollingPin.hpp"

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
    struct Level1 : public Level {
        void init() override {

            const std::vector<int>& wall_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                  -1, 0, 20, 40, 40, 40, 40, 60, 80, -1,
                                                  -1, 1, -1, -1, -1, -1, -1, -1, 81, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 83, -1,
                                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            const std::vector<int>& floor_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, 21, 41, 41, 41, 41, 61, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            collision_object = new Tilemap("Walls", 1, wall_data);

            // Give player and crab different positions

            player_object = new Player("Bob", { 32.0f, 32.0f });

            Tilemap* tilemap = new Tilemap("Floor", 0, floor_data);

            //RollingPin* rolling_pin_object1 = new RollingPin("rolling_pin_object1", 5, { 32.0f, 32.0f });

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(tilemap);
            //objects.push_back(rolling_pin_object1);
        }
    };

    struct Level2 : public Level {
        void init() override {
            const std::vector<int>& wall_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
                                                  -1, 3, -1, -1, -1, -1, -1, -1, 83, -1,
                                                  -1, 4, 24, 44, 44, 44, 44, 64, 84, -1,
                                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

            const std::vector<int>& floor_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 23, 43, 43, 43, 43, 63, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};

            collision_object = new Tilemap("Walls", 1, wall_data);
            Tilemap* floor = new Tilemap("Floor", 0, floor_data);
            player_object = new Player("Bob", { 16.0f, 32.0f });
            //the rolling pin object is the only object in level 2 not present in level 1
            RollingPin* rolling_pin_object1 = new RollingPin("rolling_pin_object1", 5, { 32.0f, 32.0f });

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(floor);
            objects.push_back(rolling_pin_object1);
        }
    };

    Level* level_1 = new Level1();
    Level* level_2 = new Level2();

    Door* to_lvl2 = new Door("to_lvl2", Vector2{ 56.0f, 32.0f });
    Door* to_lvl1 = new Door("to_lvl1", Vector2{ 8.0f, 32.0f });

    level_1->init();
    level_2->init();

    to_lvl2->set_target_level(level_2);
    to_lvl1->set_target_level(level_1);

    level_2->add_object(to_lvl1);
    level_1->add_object(to_lvl2);

    // Do not call delete on tilemap; game handles this automatically

    //current_game->add_object(tilemap);

    // Load level

    current_game->load_level(level_1);

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