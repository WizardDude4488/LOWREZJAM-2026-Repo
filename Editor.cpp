#include <iostream>
#include <string>

#include "raylib.h"

#include "Game.hpp"
#include "Tilemap.hpp"
#include "Helper.hpp"
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

    std::vector<Rectangle> tileset_rects = Helper::create_spritesheet_frames(8, 8, 160, 88, 220);

    int count = 0;
    std::string tileset_name = "sandtest";

    for (Rectangle rect : tileset_rects) {

        std::string hash = tileset_name + std::to_string(count);
        current_game->load_image_from_rect(hash, "sandtest.png", rect);
        current_game->set_tile(count, hash);
        count++;
    }

    // Create test level
    // Game doesn't handle Level's memory so we need to delete it at application close
    struct TestLevel : public Level {
        void init() override {
            collision_object = new Tilemap("Walls", 1);
            objects.push_back(collision_object);
        }
    };

    Level* test_level = new TestLevel();

    test_level->init();

    // Do not call delete on tilemap; game handles this automatically

    //current_game->add_object(tilemap);

    // Load level

    current_game->load_level(test_level);

    int copied_tile = -1;

    // Main game loop
    while (!WindowShouldClose()) {
        current_game->update();

        Vector2 mouse_tile_pos = Helper::game_pos_to_tile_pos(Helper::screen_pos_to_game_pos(GetMousePosition()));

        int tile_x = static_cast<int>(mouse_tile_pos.x);
        int tile_y = static_cast<int>(mouse_tile_pos.y);

        Tilemap* tilemap = current_game->get_collision_object();

        if (IsKeyPressed(KEY_W)) {
            tilemap->set_tile(tile_x, tile_y, tilemap->get_tile(tile_x, tile_y) - 19);
        }

        if (IsKeyPressed(KEY_S)) {
            tilemap->set_tile(tile_x, tile_y, tilemap->get_tile(tile_x, tile_y) + 19);
        }

        if (IsKeyPressed(KEY_A)) {
            tilemap->set_tile(tile_x, tile_y, tilemap->get_tile(tile_x, tile_y) - 1);
        }

        if (IsKeyPressed(KEY_D)) {
            tilemap->set_tile(tile_x, tile_y, tilemap->get_tile(tile_x, tile_y) + 1);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            copied_tile = tilemap->get_tile(tile_x, tile_y);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            tilemap->set_tile(tile_x, tile_y, copied_tile);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            tilemap->set_tile(tile_x, tile_y, -1);
        }

        current_game->draw();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    current_game->unload_level();

    std::cout << "\n\n";

    for (int x = 0; x < TRUE_WIDTH; x++) {
        for (int y = 0; y < TRUE_WIDTH; y++) {
            std::cout << test_level->collision_object->get_tile(x, y) << ", ";
            if (y == TRUE_WIDTH - 1) { std::cout << "\n"; }
        }
    }

    std::cout << "\n";

    end_game();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}