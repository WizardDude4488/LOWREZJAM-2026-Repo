#include <cmath>
#include <algorithm>

#include "Tilemap.hpp"
#include "Helper.hpp"

std::vector<Rectangle> Helper::create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height) {
	std::vector<Rectangle> rectangles;
	
	// Exclude border space that doesn't take up a full frame
	int max_width = std::floor(static_cast<double>(image_width) / static_cast<double>(frame_width));
	int max_height = std::floor(static_cast<double> (image_height) / static_cast<double>(frame_height));
							// Adjust top-left
	for (int y = 0; y < max_height; y += frame_height) {
		for (int x = 0; x < max_width; x += frame_width) {
			rectangles.push_back(Rectangle{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(frame_width), static_cast<float>(frame_height)});
		}
	}

	return rectangles;
}

std::vector<Rectangle> Helper::create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height, int num_of_frames) {
	std::vector<Rectangle> rectangles;
	
	// Exclude border space that doesn't take up a full frame
	int max_width = std::floor(static_cast<double>(image_width) / static_cast<double>(frame_width));
	int max_height = std::floor(static_cast<double> (image_height) / static_cast<double>(frame_height));
							// Adjust top-left
	int f = 0;
	while (f < num_of_frames) {
		for (int y = 0; y < image_height; y += frame_height) {
			for (int x = 0; x < image_width; x += frame_width) {
				if (f <= num_of_frames - 1) {
					rectangles.push_back(Rectangle{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(frame_width), static_cast<float>(frame_height)});
					f++;
				} else {
					return rectangles;
				}
				
			}
		}
	}

	return rectangles;
}

Vector2 Helper::game_pos_to_tile_pos(Vector2 pos) {
	return Vector2{
		std::max(std::min(static_cast<float>(static_cast<int>(std::floor(pos.x)) / TILE_WIDTH) + 1.0f, TRUE_WIDTH - 1.0f), 0.0f),
		std::max(std::min(static_cast<float>(static_cast<int>(std::floor(pos.y)) / TILE_WIDTH) + 1.0f, TRUE_WIDTH - 1.0f), 0.0f)
	};
}

Vector2 Helper::tile_pos_to_game_pos(Vector2 tile_pos) {
	return Vector2{
		(tile_pos.x * static_cast<float>(TILE_WIDTH)) - static_cast<float>(TILE_WIDTH),
		(tile_pos.y * static_cast<float>(TILE_WIDTH)) - static_cast<float>(TILE_WIDTH)
	};
}

Vector2 Helper::screen_pos_to_game_pos(Vector2 screen_pos) {
    float target_length = static_cast<float>(std::min(GetScreenWidth(), GetScreenHeight()));
    Vector2 window_size = { static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };

    Rectangle canvas_target_rect;
    if (window_size.x >= window_size.y) {
        canvas_target_rect = { (window_size.x - target_length) / 2.0f, 0.0f, target_length, target_length };
    }
    else {
        canvas_target_rect = { 0.0f, (window_size.y - target_length) / 2.0f, target_length, target_length };
    }

    float scale = 64.0f / target_length; // e.g. 64 / target_length

    return Vector2{
        (screen_pos.x - canvas_target_rect.x) * scale,
        (screen_pos.y - canvas_target_rect.y) * scale
    };
}

bool Helper::colliding_with_tile(Rectangle object_bounds, Tilemap* tilemap) {
    Vector2 tile_tl = { object_bounds.x, object_bounds.y };
    Vector2 tile_tr = { object_bounds.x + object_bounds.width, object_bounds.y };
    Vector2 tile_bl = { object_bounds.x, object_bounds.y + object_bounds.height };
    Vector2 tile_br = { object_bounds.x + object_bounds.width, object_bounds.y + object_bounds.height };

    Vector2 final_tl = game_pos_to_tile_pos(Vector2Add(tile_tl, Vector2{ -1.0f, -1.0f }));
    Vector2 final_tr = game_pos_to_tile_pos(Vector2Add(tile_tr, Vector2{ 1.0f, -1.0f }));
    Vector2 final_bl = game_pos_to_tile_pos(Vector2Add(tile_bl, Vector2{ -1.0f, 1.0f }));
    Vector2 final_br = game_pos_to_tile_pos(Vector2Add(tile_br, Vector2{ 1.0f, 1.0f }));

    for (int x = static_cast<int>(final_tl.x); x <= static_cast<int>(final_tr.x); x++) {
        for (int y = static_cast<int>(final_tl.y); y <= static_cast<int>(final_bl.y); y++) {
            if (tilemap->get_tile(x, y) != -1) {
                Vector2 world_pos = tile_pos_to_game_pos(Vector2{ (float)x, (float)y });
                Rectangle tile_rect = { world_pos.x, world_pos.y, static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH) };
                bool collision = CheckCollisionRecs(object_bounds, tile_rect);

                if (collision) { return true; }
            }
        }
    }

    return false;
}

Vector2 Helper::calculate_tile_collision(Rectangle object_bounds, Tilemap* tilemap) {
    Vector2 tile_tl = { object_bounds.x, object_bounds.y };
    Vector2 tile_tr = { object_bounds.x + object_bounds.width, object_bounds.y };
    Vector2 tile_bl = { object_bounds.x, object_bounds.y + object_bounds.height };
    Vector2 tile_br = { object_bounds.x + object_bounds.width, object_bounds.y + object_bounds.height };

    Vector2 final_tl = game_pos_to_tile_pos(Vector2Add(tile_tl, Vector2{ -1.0f, -1.0f }));
    Vector2 final_tr = game_pos_to_tile_pos(Vector2Add(tile_tr, Vector2{ 1.0f, -1.0f }));
    Vector2 final_bl = game_pos_to_tile_pos(Vector2Add(tile_bl, Vector2{ -1.0f, 1.0f }));
    Vector2 final_br = game_pos_to_tile_pos(Vector2Add(tile_br, Vector2{ 1.0f, 1.0f }));

    Vector2 object_center = { object_bounds.x + object_bounds.width / 2.0f, object_bounds.y + object_bounds.height / 2.0f };

    float min_x = -std::numeric_limits<float>::infinity();
    float max_x = std::numeric_limits<float>::infinity();
    float min_y = -std::numeric_limits<float>::infinity();
    float max_y = std::numeric_limits<float>::infinity();

    for (int x = static_cast<int>(final_tl.x); x <= static_cast<int>(final_tr.x); x++) {
        for (int y = static_cast<int>(final_tl.y); y <= static_cast<int>(final_bl.y); y++) {
            if (tilemap->get_tile(x, y) != -1) {
                Vector2 world_pos = tile_pos_to_game_pos(Vector2{ (float)x, (float)y });
                Rectangle tile_rect = { world_pos.x, world_pos.y, static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_WIDTH) };
                Rectangle collision = GetCollisionRec(object_bounds, tile_rect);

                if (collision.width <= 0.0f || collision.height <= 0.0f) { continue; }

                Vector2 tile_center = { tile_rect.x + tile_rect.width / 2.0f, tile_rect.y + tile_rect.height / 2.0f };

                // Only let this tile constrain the axis it's actually blocking --
                // the one with the shallower overlap. A tile barely grazed on one
                // axis shouldn't be able to clamp the other axis.
                if (collision.width < collision.height) {
                    if (object_center.x < tile_center.x) {
                        max_x = std::min(max_x, tile_rect.x - object_bounds.width);
                    }
                    else {
                        min_x = std::max(min_x, tile_rect.x + tile_rect.width);
                    }
                }
                else {
                    if (object_center.y < tile_center.y) {
                        max_y = std::min(max_y, tile_rect.y - object_bounds.height);
                    }
                    else {
                        min_y = std::max(min_y, tile_rect.y + tile_rect.height);
                    }
                }
            }
        }
    }

    float new_x = (min_x <= max_x) ? std::max(min_x, std::min(object_bounds.x, max_x)) : object_bounds.x;
    float new_y = (min_y <= max_y) ? std::max(min_y, std::min(object_bounds.y, max_y)) : object_bounds.y;

    return Vector2{ new_x, new_y };
}

Vector2 get_animation_center(const Animation& anim) {
    const Rectangle& rect = anim.get_frame_rect(0);
    return Vector2{ rect.width / 2.0f, rect.height / 2.0f };
}