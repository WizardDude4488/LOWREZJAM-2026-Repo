#pragma once

#include "Tilemap.hpp"
#include "Player.hpp"

class Level {
private:
	std::vector<Room*> rooms;
public:
	Player* reset(); // Gives a pointer to the new player object
					 // Run this when loading game or dying
	Room* get_room(int index);
};