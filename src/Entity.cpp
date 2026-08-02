#include "Entity.hpp"

void Entity::set_position(Vector2 position) {
	bounds = { position.x, position.y, bounds.width, bounds.height };
}

Vector2 Entity::get_position() {
	return Vector2{ bounds.x, bounds.y };
}

Rectangle Entity::get_bounds() {
	return bounds;
}