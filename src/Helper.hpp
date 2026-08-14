#pragma once

#include <vector>

#include "raylib.h"
#include "Tilemap.hpp"
#include "Animation.hpp"

namespace Helper {
	// Go left to right, top to bottom creating rects representing regions of the spritesheet
	std::vector<Rectangle> create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height);

    std::vector<Rectangle> create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height, int num_of_frames);

	Vector2 game_pos_to_tile_pos(Vector2 pos);

	Vector2 tile_pos_to_game_pos(Vector2 tile_pos);

	Vector2 screen_pos_to_game_pos(Vector2 screen_pos);

	bool colliding_with_tile(Rectangle object_bounds, Tilemap* tilemap);

	Vector2 calculate_tile_collision(Rectangle object_bounds, Tilemap* tilemap);

	Vector2 get_animation_center(const Animation& anim);

	// If collider is smaller than sprite, make sure sprite encapsulates collider equally in all directions
	// Return the difference
	Vector2 adjust_sprite_to_collider(Vector2 collider_size, Vector2 sprite_size);

	Color calculate_hurt_flash(float hurt_time);
}