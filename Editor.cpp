#include <iostream>
#include <string>

#include "raylib.h"

#include "Game.hpp"
#include "Entity.hpp"
#include "Tilemap.hpp"
#include "Helper.hpp"
#include "Load.hpp"
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

    load_assets();

    // Create test level
    // Game doesn't handle Room's memory so we need to delete it at application close

    Tilemap* select_tile = new Tilemap("Select", 1);

    class HighlightTile : public Object {
    protected:
        std::string class_name = "HighlightTile";
    public:
        HighlightTile() { draw_layer = 3; name = "HighlightTile"; }

        // From Object.hpp

        const std::string& get_class() const override { return class_name; }
        void update(float dt) override { return; }
        void draw() override { 
            Vector2 screen_tile_pos = Helper::tile_pos_to_game_pos(Helper::game_pos_to_tile_pos(Helper::screen_pos_to_game_pos(GetMousePosition())));
            DrawRectangle(screen_tile_pos.x, screen_tile_pos.y, 8, 8, Color{ 255, 0, 255, 100 });
        }
    };

    Room* test_level = new Room();

    HighlightTile* highlight = new HighlightTile();
    Tilemap* collision_object = new Tilemap("Walls", 0);
    
    test_level->add_object(collision_object);
    test_level->collision_object = collision_object;
    test_level->add_object(select_tile);
    test_level->add_object(highlight);

    // Do not call delete on tilemap; game handles this automatically

    //current_game->add_object(tilemap);

    // Load level

    current_game->__load_level(test_level);

    enum EditorState {EDIT_TILEMAP = 0, EDIT_ENTITIES = 1, SELECT_TILEMAP = 2, SELECT_ENTITIES = 3};
    EditorState current_state = EDIT_TILEMAP;

    // EDIT_TILEMAP
    int copied_tile = -1;
    // SELECT_TILEMAP
    int view_position_x = 0;
    int view_position_y = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        current_game->update();

        Vector2 mouse_tile_pos = Helper::game_pos_to_tile_pos(Helper::screen_pos_to_game_pos(GetMousePosition()));

        int tile_x = static_cast<int>(mouse_tile_pos.x);
        int tile_y = static_cast<int>(mouse_tile_pos.y);

        Tilemap* tilemap = current_game->get_collision_object();

        if (IsKeyPressed(KEY_ONE)) {
            current_state = EDIT_TILEMAP;
            std::cout << "EDIT_TILEMAP\n";
        }

        if (IsKeyPressed(KEY_TWO)) {
            current_state = EDIT_ENTITIES;
            std::cout << "EDIT_ENTITIES\n";
        }

        if (IsKeyPressed(KEY_THREE)) {
            current_state = SELECT_TILEMAP;
            std::cout << "SELECT_TILEMAP\n";
        }

        if (IsKeyPressed(KEY_FOUR)) {
            current_state = SELECT_ENTITIES;
            std::cout << "SELECT_ENTITIES\n";
        }

        if (current_state == EDIT_TILEMAP) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { // Set
                tilemap->set_tile(tile_x, tile_y, copied_tile);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) { // Clear
                tilemap->set_tile(tile_x, tile_y, -1);
            }
            // Make sure select tilemap is cleared
            for (int x = 1; x < TRUE_WIDTH - 1; x++) {
                for (int y = 1; y < TRUE_WIDTH - 1; y++) {
                    select_tile->set_tile(x, y, -1);
                }
            }
        } else if (current_state == SELECT_TILEMAP) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                copied_tile = (tile_x + view_position_x) + (tile_y + view_position_y) * 20;
            }

            if (IsKeyPressed(KEY_S)) {
                view_position_y += 1;
            }

            if (IsKeyPressed(KEY_W)) {
                view_position_y -= 1;
            }

            if (IsKeyPressed(KEY_A)) {
                view_position_x -= 1;
            }

            if (IsKeyPressed(KEY_D)) {
                view_position_x += 1;
            }

            // Arrange tiles into tilemap
            // Only set in areas that are visible on screen
            for (int x = 1; x < TRUE_WIDTH - 1; x++) {
                for (int y = 1; y < TRUE_WIDTH - 1; y++) {
                    select_tile->set_tile(x, y, (x + view_position_x) + 20 * (y + view_position_y));
                }
            }
        }

        // Draw tilemap
        current_game->begin_draw();
        current_game->end_draw();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    current_game->__unload_level();

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