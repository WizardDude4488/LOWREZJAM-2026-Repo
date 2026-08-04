#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "Helper.hpp"
#include "Game.hpp"
#include "Bullet.hpp"

Bullet::Bullet(const std::string& n, Vector2 pos, Vector2 dir, float s) {
	name = n;
	draw_layer = 2; // Might change later
	bounds = Rectangle{ pos.x, pos.y, 3, 3 };
	animation = Animation("bullet", std::vector<Rectangle>{Rectangle{0.0f, 0.0f, 3.0f, 3.0f}});
	speed = s;
	direction = Vector2Normalize(dir);
}

const std::string& Bullet::class_name = "Bullet";

const std::string& Bullet::get_class() const {
	return class_name;
}

void Bullet::update(float dt) {
	velocity = Vector2Scale(direction, speed * dt);
	set_position(get_position() + velocity);

	// If touching player or wall, delete itself
	if (Helper::colliding_with_tile(bounds, current_game->get_collision_object()) || CheckCollisionRecs(bounds, current_game->get_player_object()->get_bounds())) { current_game->remove_object(this); }
}

void Bullet::draw() {
	animation.draw_frame(get_position());
}

void Bullet::touch(const Object* from) {
	//if (!(dynamic_cast<Pirate*>(from))) { current_game->remove_object(this); }
	return;
}