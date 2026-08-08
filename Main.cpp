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
                                                  -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, 0, 0, 0, 0, 0, 0, 0, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, 0, -1, -1, -1, -1, -1, -1, 0, -1,
                                                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            const std::vector<int>& floor_data = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, 21, 41, 41, 41, 41, 61, -1, -1,
                                                   -1, -1, 23, 43, 43, 43, 43, 63, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, 21, 41, 41, 41, 41, 61, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
                                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, };

            collision_object = new Tilemap("Walls", 1, wall_data);

            // Give player and crab different positions

            player_object = new Player("Bob", { 32.0f, 32.0f });

            Tilemap* tilemap = new Tilemap("Floor", 0, floor_data);

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(tilemap);
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

            objects.push_back(player_object);
            objects.push_back(collision_object);
            objects.push_back(floor);
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

    // Disable quitting game by pressing esc
    SetExitKey(KEY_NULL);

    // Hide default cursor
    HideCursor();

    // Main game loop
    enum GameState {INGAME, PAUSEM, SETM, MINIMAP};
    GameState last_state = PAUSEM;
    GameState current_state = INGAME;

    int sound_volume = 5;
    int music_volume = 5;

    bool should_exit = false;

    auto ExecMainPauseMenu = [&]() {
            DrawRectangle(0, 0, 64, 64, Color{ 75, 75, 100, 100 }); // Draw background
            
            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 8.0f, 64.0f, 10.0f })) {
                DrawRectangle(0, 8, 64, 8, Color{ 50, 50, 100, 150 }); // Draw higlight
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_state = SETM;
                }
            }

            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 16.0f, 64.0f, 10.0f })) {
                DrawRectangle(0, 16, 64, 8, Color{ 50, 50, 100, 150 });
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    should_exit = true;
                }
            }
            
            // Draw text over highlight
            DrawText("PAUSED",   0,  0,  8, RAYWHITE);
            DrawText("SETTINGS", 0,  8,  8, RAYWHITE);
            DrawText("QUIT?",    0, 16,  8, RAYWHITE);
        };

    auto ExecSettingMenu = [&]() {
            DrawRectangle(0, 0, 64, 64, Color{ 75, 75, 100, 100 }); // Draw background
            
            
            
            // Detect button press
            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 8.0f, 64.0f, 8.0f })) {
                DrawRectangle(0, 8, 64, 8, Color{ 50, 50, 100, 150 });
                
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { // Detect mouse button press
                    music_volume = (music_volume + 1) % 11;
                }
            }
            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 16.0f, 64.0f, 8.0f })) {
                DrawRectangle(0, 16, 64, 8, Color{ 50, 50, 100, 150 });
                
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    sound_volume = (sound_volume + 1) % 11;
                }
            }
            // Draw text over highlight
            DrawText("PAUSED", 0, 0, 8, RAYWHITE); // Draw labels
            DrawText("MUSIC", 0,  8, 8, RAYWHITE);
            DrawText("SOUND", 0, 16, 8, RAYWHITE);
            
            // Get current setting text
            std::string sound = std::to_string(sound_volume);
            std::string music = std::to_string(music_volume);
            sound.resize(2);
            music.resize(2);

            DrawText(music.c_str(), 64 - MeasureText(music.c_str(), 8), 8, 8, RAYWHITE); // Draw values
            DrawText(sound.c_str(), 64 - MeasureText(sound.c_str(), 8), 16, 8, RAYWHITE);

            // TODO: Set music and sound volume
        };

    while (!should_exit) {

        should_exit = WindowShouldClose();

        if (IsKeyPressed(KEY_ESCAPE)) {
            current_state = (current_state == INGAME) ? PAUSEM : INGAME;
        }

        if (current_state == INGAME) {
            current_game->update();
        }
        
        current_game->begin_draw();

        switch (current_state) {
        case PAUSEM: { ExecMainPauseMenu(); break; }
        case SETM: { ExecSettingMenu(); break; }
        }

        // Draw pixel art cursor
        if (current_state != INGAME) {
            Vector2 pos = Helper::screen_pos_to_game_pos(GetMousePosition());
            DrawTexture(current_game->get_texture("cursor"), static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
        }

        current_game->end_draw();
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