#pragma once

#include <vector>

#include "raylib.h"

#include "Object.hpp"
#include "Game.hpp"

#define TILE_WIDTH 4
#define TILEMAP_WIDTH (64 / TILE_WIDTH) // 64 / tile_width
#define TRUE_WIDTH (TILEMAP_WIDTH + 2)

class Tilemap : public Object {
protected:
	// Add 2 so we can have border / wall tiles outside screen that don't render
	int tiles[TRUE_WIDTH][TRUE_WIDTH]; // x, then y
	// NOTE:
	// x -> inf, sprite_x -> inf
	// y -> inf, sprite_y -> -inf
	// centered at top left

public:
	Tilemap(const std::string& n, int layer);

	void update(const Game* g, float dt) override;
	void draw(const Game* g) override;

	void set_tile(int x, int y, int id);
	void set_square(int start_x, int start_y, int end_x, int end_y, int id);
	void set_square_filled(int start_x, int start_y, int end_x, int end_y, int id);

	int get_tile(int x, int y);
};