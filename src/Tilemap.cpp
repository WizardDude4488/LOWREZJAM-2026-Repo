#include "Tilemap.hpp"

Tilemap::Tilemap(const std::string& n, int layer) {
	name = n;
	draw_layer = layer;
	for (int x = 0; x < TRUE_WIDTH; x++) {
		for (int y = 0; y < TRUE_WIDTH; y++) {
			tiles[x][y] = -1;
		}
	}
}

void Tilemap::update(const Game* g, float dt) {
	return; // Tilemap is not updateable
}

void Tilemap::draw(const Game* g) {
	// Increment through all tiles
	for (int x = 0; x < TRUE_WIDTH; x++) {
		for (int y = 0; y < TRUE_WIDTH; y++) {
			if (tiles[x][y] != -1) {
				DrawTexture(g->get_image(g->get_tile(tiles[x][y])), (x * TILE_WIDTH) - TILE_WIDTH, (y * TILE_WIDTH) - TILE_WIDTH, WHITE);
			}
		}
	}
}

void Tilemap::set_tile(int x, int y, int id) {
	if (x > -1 && x < TRUE_WIDTH) {
		if (y > -1 && y < TRUE_WIDTH) {
			tiles[x][y] = id;
		}
	}
}

void Tilemap::set_square(int start_x, int start_y, int end_x, int end_y, int id) {
	// Only fill in borders

	// Top segment
	for (int i = start_x; i <= end_x; i++) {
		this->set_tile(i, start_y, id);
	}

	// Bottom segment
	for (int i = start_x; i <= end_x; i++) {
		this->set_tile(i, end_y, id);
	}

	// Left segment
	for (int i = start_y; i <= end_y; i++) {
		this->set_tile(start_x, i, id);
	}

	// Right segment
	for (int i = start_y; i <= end_y; i++) {
		this->set_tile(end_x, i, id);
	}
}

void Tilemap::set_square_filled(int start_x, int start_y, int end_x, int end_y, int id) {
	for (int x = start_x; x <= end_x; x++) {
		for (int y = start_y; y <= end_y; y++) {
			this->set_tile(x, y, id);
		}
	}
}

int Tilemap::get_tile(int x, int y) {
	if (x > -1 && x < TRUE_WIDTH) {
		if (y > -1 && y < TRUE_WIDTH) {
			return tiles[x][y];
		}
	}

	return -1;
}