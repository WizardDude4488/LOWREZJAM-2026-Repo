#pragma once

#include "raylib.h"
#include "Tilemap.hpp"
#include "Entity.hpp"


// NOTE: See the Room struct for a proper explanation of doors

class Door : public Entity {
protected:
	Room* target_level = nullptr;
	bool open = true; // If true, players can pass through the door
	static const std::string& class_name;
public:
	// target_level is not set here.
	// There will be a function link_doors that sets the target_level after all levels have been created
	// If we set target_level here then the pointer could point to the wrong level or 
	Door(const std::string& n, Rectangle bounds);
	const std::string& get_class() const override;

	void update(float dt) override;
	void draw() override;

	void touch(const Object* from) override;

	void set_target_level(Room* level);
	Room* get_target_level();

	void open_door();
	void close_door();
};