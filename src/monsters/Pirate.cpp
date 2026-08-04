#include <vector>

#include "Game.hpp"
#include "Helper.hpp"
#include "Object.hpp"
#include "Bullet.hpp"
#include "Pirate.hpp"
#include "Player.hpp"

const std::string Pirate::class_name = "Pirate";

Pirate::Pirate(const std::string& n, Vector2 pos, float radius) {
	name = n;
	draw_layer = 3;
	bounds = { pos.x, pos.y, 12.0f, 12.0f };
	target_radius = radius;
	animation = Animation("pirate", Helper::create_spritesheet_frames(6, 6, 64, 64, 1) );
	max_health = 25;
	health = max_health;
}

const std::string& Pirate::get_class() const {
	return class_name;
}

void Pirate::update(float dt) {
	state_time += dt;

	Player* player_object = current_game->get_player_object();

	float distance_to_player = Vector2Distance(get_position(), player_object->get_position());
	Vector2 direction = Vector2Normalize(player_object->get_position() - get_position());

	if (state_time >= 4.0f) {
		// If player is close enough, shoot
		if (distance_to_player <= target_radius) {
			Bullet* bullet = new Bullet("PirateBullet", get_position(), direction, 30.0f);
			current_game->add_object(bullet);
			state_time = 0.0f;
		}
	}

	if (distance_to_player <= target_radius) {
		// Update player position continuously
		direction = Vector2Normalize(player_object->get_position() - get_position());
		Vector2 delta = Vector2Scale(direction, dt * walk_speed); // Calculate speed
		// Same strategy as in Crab
		if (Vector2Distance(delta + get_position(), get_position()) > Vector2Distance(get_position(), player_object->get_position())) {
			set_position(player_object->get_position()); // Teleport
		}
		else {
			set_position(delta + get_position()); // Don't; Just move normally
		}
	}
}

void Pirate::draw() {
	animation.draw_frame(Vector2{bounds.x, bounds.y});
}

void Pirate::touch(const Object* from) {
	return;
}

void Pirate::die() {
	current_game->remove_object(this);
}

void Pirate::hurt(int amount) {
	health -= amount;
	if (health <= 0) {
		die();
	}
}