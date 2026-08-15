#include "Level.hpp"
#include "items/Lobster.hpp"
#include "monsters/Crab.hpp"

Player* Level::reset() {
	// Create the levels
	// Change when proper level design is introduced
	rooms.clear();

	Room* beach1 = new Room();
	beach1->add_object(new Tilemap("floor", 0, std::vector<int>{
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, 21, 41, 41, 41, 41, 61, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, 22, 42, 42, 42, 42, 62, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	}));

	Tilemap* walls = new Tilemap("walls", 1, std::vector<int>{
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, 0, 20, 40, 40, 40, 40, 60, 0, -1,
		-1, 1, -1, -1, -1, -1, -1, -1, 81, -1,
		-1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
		-1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
		-1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
		-1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
		-1, 2, -1, -1, -1, -1, -1, -1, 82, -1,
		-1, 2, 226, 306, -1, -1, 226, 306, 82, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	});

	beach1->add_object(walls);

	beach1->add_object(new Lobster("Lobster", {48.0f, 48.0f}));

	beach1->add_object(new Crab("Crab", { 48.0f, 16.0f }, { 48.0f, 32.0f }, 15.0f));

	beach1->collision_object = walls;

	beach1->player_position = { 32.0f, 32.0f };

	rooms.push_back(beach1);

	Player* player = new Player("player", {0.0f, 0.0f} );

	return player;
}

Room* Level::get_room(int index) {
	return rooms.at(index);
}