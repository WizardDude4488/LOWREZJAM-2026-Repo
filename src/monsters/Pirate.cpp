#include <vector>

#include "Game.hpp"
#include "Helper.hpp"
#include "Object.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

#include "Pirate.hpp"

const std::string Pirate::class_name = "Pirate";

Pirate::Pirate(const std::string& n, Vector2 pos, float radius) {
	name = n;
	draw_layer = 3;
	bounds = { pos.x, pos.y, 12.0f, 12.0f };
	target_radius = radius;
	animation = Animation("pirate", Helper::create_spritesheet_frames(12, 12, 132, 132, 48) );
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
			Bullet* bullet = new Bullet("PirateBullet", get_position(), direction, 20.0f);
			current_game->add_object(bullet);
			state_time = 0.0f;
			anim_state = ATTACK;
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

		if (abs(direction.x) > abs(direction.y)) {
			if (direction.x < 0.0f) {
				anim_direction = LEFT;
			} else if (direction.x > 0.0f) {
				anim_direction = RIGHT;
			}
		} else {
			if (direction.y < 0.0f) {
				anim_direction = BACK;
			} else if (direction.y > 0.0f) {
				anim_direction = FORWARD;
			}
		}

		

		if (anim_state != ATTACK) { anim_state = WALK; }
	} else {
		direction = { 0.0f, 0.0f };
	}

	// Calculate collision
	Vector2 collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
	set_position(collision);

	// Animation (Copied from player)
	if (last_anim_state != anim_state) {
		anim_time = 0.0f;
		anim_counter = 0;
	}

	if (anim_state == WALK) {
		// If in walking state but not moving
		if (direction == Vector2{0.0f, 0.0f}) {
			// Go back to IDLE state
			anim_state = IDLE;
		}
	}

	if (anim_state == ATTACK) {
		// If animation is finished
		if (anim_time >= 0.8f) {
			anim_state = IDLE;
		}
	}

	anim_time += dt;

	while (anim_time >= 0.2) {
		anim_counter = (anim_counter + 1) % 4; // All of the animations in pirate.png have the same number of frames
		anim_time -= 0.2;
	}

	animation.set_frame(anim_direction + anim_state + anim_counter);

	last_anim_state = anim_state;
}

void Pirate::draw() {
	animation.draw_frame(Vector2{bounds.x, bounds.y});
}

void Pirate::touch(const Object* from) {
	//add hurt() for rolling pin
    if (from->get_class() == "RollingPin") {
        hurt(5);
        std::cout << "\nPirate took five damage.";
    }
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
