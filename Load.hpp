#include "raylib.h"
#include "Game.hpp"
#include "Helper.hpp"

void load_assets() {

    std::vector<Rectangle> tileset_rects = Helper::create_spritesheet_frames(8, 8, 160, 88, 220);

    int count = 0;
    std::string tileset_name = "sandtest";

    for (Rectangle rect : tileset_rects) {

        std::string hash = tileset_name + std::to_string(count);
        current_game->load_image_from_rect(hash, "sandtest.png", rect);
        current_game->set_tile(count, hash);
        count++;
    }

    // Add more tilesets here

    current_game->load_image("yellow-guy", "yellow-guy.png");

    current_game->load_image("crab", "crab.png");

    current_game->load_image("seagull", "seagull.png");

    current_game->load_image("bullet", "bullet.png");

    current_game->load_image("pirate", "pirate.png");

    current_game->load_image("rolling-pin", "rolling-pin.png");

    current_game->load_image("door", "door-placeholder.png");
}