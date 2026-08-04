#pragma once

#include <vector>

#include "raylib.h"

#include "Object.hpp"
#include "Entity.hpp"
#include "Player.hpp" // Replace with Player.hpp when impl.

#define TILE_WIDTH 8
#define TILEMAP_WIDTH (64 / TILE_WIDTH) // 64 / tile_width
#define TRUE_WIDTH (TILEMAP_WIDTH + 2)

class Tilemap : public Object {
protected:
	static const std::string class_name;
	// Add 2 so we can have border / wall tiles outside screen that don't render
	int tiles[TRUE_WIDTH][TRUE_WIDTH]; // x, then y
	// NOTE:
	// x -> inf, sprite_x -> inf
	// y -> inf, sprite_y -> -inf
	// centered at top left

public:
	Tilemap(const std::string& n, int layer);
	Tilemap(const std::string& n, int layer, const std::vector<int>& data);
	const std::string& get_class() const override;

	void update(float dt) override;
	void draw() override;

	void set_tile(int x, int y, int id);
	void set_square(int start_x, int start_y, int end_x, int end_y, int id);
	void set_square_filled(int start_x, int start_y, int end_x, int end_y, int id);

	int get_tile(int x, int y);
};

// NOTE: This deserves a bit of explanation
// In our project ideas, we have ideas for a number of levels.
// The levels in our ideas are not the same as the Level class.
// One level that we want to make might have multiple Level
// instances corresponding to different rooms.
// This simplifies the implementation of doors, because then
// we don't have to have a different implementation of a door
// depending on if we are going to a different room or a new level

struct Level {
	std::vector<Object*> objects;
	Player* player_object;
	Tilemap* collision_object;

	~Level();
	virtual void init() = 0; // Make specific level here
};