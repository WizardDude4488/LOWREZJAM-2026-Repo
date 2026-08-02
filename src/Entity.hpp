#pragma once

#include "raylib.h"

#include "Object.hpp"
#include "Animation.hpp"

// abstract; cannot be directly instanced
// (it inherits virtual methods from Object)
class Entity : public Object {
protected:
	// Bounds should be defined per-class, not per-instance
	Rectangle bounds; // Store position and size
	Animation animation; // Store ref to texture and current frame
public:
	virtual ~Entity() = default;

	virtual const std::string& get_class() const = 0;

	void set_position(Vector2 position);
	Vector2 get_position();

	// Probably wont need set_size and set_position

	Rectangle get_bounds(); // use for collision

	// Called by other objects when two objects are touching
	// In the same vein of functionality / purpose as Object::update and Object::draw
	virtual void touch(const Object* from) = 0;
};