#include <iostream>

#include "Game.hpp"
#include "Helper.hpp"
#include "Door.hpp"

const std::string& Door::class_name = "Door";

Door::Door(const std::string& n, Vector2 position) {
	name = n;
	bounds = {position.x, position.y, 4.0f, 4.0f}; // Make it 4x4 for now
	animation = Animation("door", Helper::create_spritesheet_frames(4, 4, 4, 4));
	animation.set_frame(0);
}

const std::string& Door::get_class() const {
	return class_name;
}

void Door::update(float dt) {
	return; // I don't think anything needs to be done here
}

void Door::draw() {
	animation.draw_frame(Vector2{bounds.x, bounds.y});
}

void Door::touch(const Object* from) {
	if (from->get_class() == "Player") {
		// Switch level to target_level
		if (open) {
			if (target_level != nullptr) {
				current_game->load_level(target_level);
			} else {
				std::cout << "Door: attempted to load level from nullptr\n";
			}
		}
		
	}
}

void Door::set_target_level(Level* level) {
	target_level = level;
}

Level* Door::get_target_level() {
	return target_level;
}

void Door::open_door() {
	open = true;
	// Play open door SFX
}

void Door::close_door() {
	open = false;
	// Play close door SFX
}