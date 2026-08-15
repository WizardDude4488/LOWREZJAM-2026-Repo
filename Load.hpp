#include "raylib.h"
#include "Game.hpp"
#include "Helper.hpp"

void load_tileset(const std::string& image_path, const std::string& tileset_hash, const std::vector<Rectangle>& rects, int* count) {
    for (Rectangle rect : rects) {

        std::string hash = tileset_hash + std::to_string(*count);
        current_game->load_image_from_rect(hash, image_path, rect);
        current_game->set_tile(*count, hash);
        (*count)++;
    }
}

void load_assets() {

    int count = 0;

    std::vector<Rectangle> rects = Helper::create_spritesheet_frames(8, 8, 160, 88, 220);

    load_tileset("sandtest.png", "sandtest", rects, &count);

    load_tileset("sandwalls.png", "sandwalls", rects, &count);

    load_tileset("grasstiles.png", "grasstiles", rects, &count);

    // Add more tilesets here

    // Load images
    
    current_game->load_image("cursor", "cursor.png");

    current_game->load_image("player", "player.png");

    current_game->load_image("crab", "crab.png");

    current_game->load_image("seagull", "seagull.png");

    current_game->load_image("bullet", "bullet.png");

    current_game->load_image("pirate", "pirate.png");

    current_game->load_image("rolling-pin2", "rolling-pin2.png");

    current_game->load_image("door", "door-placeholder.png");

    // Load sounds

    current_game->load_sound("snd-test", "crab.ogg");

    // Load music

    current_game->load_track("msc-test", "water-level.ogg");
}