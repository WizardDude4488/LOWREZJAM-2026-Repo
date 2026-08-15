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
#include "Level.hpp"

int main(void) {
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Initialize Audio
    InitAudioDevice();

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
    

    // Do not call delete on tilemap; game handles this automatically

    //current_game->add_object(tilemap);

    // Now that level only holds the player's position, we need to make sure to create a player object first

    Level* level = new Level();

    current_game->player_object = level->reset();

    current_game->__load_level(level->get_room(0));

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
            
            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 8.0f, 64.0f, 8.0f })) {
                DrawRectangle(0, 8, 64, 8, Color{ 50, 50, 100, 150 }); // Draw higlight
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_state = SETM;
                }
            }

            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 16.0f, 64.0f, 8.0f })) {
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
                    current_game->set_track_volume(static_cast<float>(music_volume) / 10.0f);
                }
            }
            if (CheckCollisionPointRec(Helper::screen_pos_to_game_pos(GetMousePosition()), Rectangle{ 0.0f, 16.0f, 64.0f, 8.0f })) {
                DrawRectangle(0, 16, 64, 8, Color{ 50, 50, 100, 150 });
                
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    sound_volume = (sound_volume + 1) % 11;
                    current_game->set_sound_volume(static_cast<float>(sound_volume) / 10.0f);
                    PlaySound(current_game->get_sound("snd-test"));
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

    current_game->set_current_track("msc-test");

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

        current_game->update_current_track();

        
        
        
        
        
        current_game->empty_queue();

        // Make sure to update music
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