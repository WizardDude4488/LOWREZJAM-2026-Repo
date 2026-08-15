#include <iostream>
#include <vector>
#include <cmath>

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Game.hpp"
#include "Helper.hpp"
#include "Crab.hpp"

using namespace Helper;


Crab::Crab(const std::string& n, Vector2 start_pos, Vector2 end_pos, float s) {
    name = n;
    draw_layer = 3;
    start_position = start_pos;
    end_position = end_pos;
    bounds = {start_pos.x, start_pos.y, bound_size.x, bound_size.y};
    animation = Animation("crab", create_spritesheet_frames(12, 12, 132, 132, 15));
    max_health = 20;
    health = max_health;
    speed = s;
}

const std::string Crab::class_name = "Crab";

const std::string& Crab::get_class() const {
    return class_name;
}

void Crab::update(float dt) {

    direction = (current_state == TO_START) ? (start_position - get_position()) : (end_position - get_position()) ;
    direction = Vector2Normalize(direction);

    // Determine anim_direction
    if (abs(direction.x) > abs(direction.y)) {
        if (direction.x < 0.0f) {
            anim_direction = LEFT;
        }
        else if (direction.x > 0.0f) {
            anim_direction = RIGHT;
        }
    }
    else {
        if (direction.y < 0.0f) {
            anim_direction = BACK;
        }
        else if (direction.y > 0.0f) {
            anim_direction = FORWARD;
        }
    }

    // When we reach the start point, switch to TO_END and vice versa
    if (current_state == TO_START && get_position() == start_position) {
        current_state = TO_END;
    } else if (current_state == TO_END && get_position() == end_position) {
        current_state = TO_START;
    }


    velocity = Vector2Scale(direction, speed);

    Vector2 delta = {0.0f, 0.0f};
    delta = Vector2Scale(velocity, dt);

    // Determine if the next position we are about to go to is the shorter path to the next point
    // If it is not, simply teleport to the next point. This prevents overshooting the target
    if (current_state == TO_START) {
        if (Vector2Distance(delta + get_position(), start_position) > Vector2Distance(get_position(), start_position)) { 
            set_position(start_position); // Teleport
        }
        else {
            set_position(delta + get_position()); // Don't; Just move normally
        }
    }
    else if (current_state == TO_END) {
        if (Vector2Distance(delta + get_position(), end_position) > Vector2Distance(get_position(), end_position)) {
            set_position(end_position);
        }
        else {
            set_position(delta + get_position());
        }
    }

    anim_time += dt;
    flash_time -= dt;

    while (anim_time >= 0.2f) {
        if (anim_direction == FORWARD || anim_direction == BACK) {
            anim_counter = (anim_counter + 1) % 4; // They have 4 frames
        } else {
            anim_counter = (anim_counter + 1) % 2; // They have 2 frames
        }
        anim_time -= 0.2;
    }

    animation.set_frame(anim_direction + anim_counter);

    // Check for collision with player

    if (CheckCollisionRecs(bounds, current_game->get_player_object()->get_bounds())) {
        current_game->get_player_object()->touch(this);
    }

    // Collision with walls
    Vector2 collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
    set_position(collision);
}

void Crab::draw() {
    if (flash_time > 0.0f) {
        animation.draw_frame(get_position() + Helper::adjust_sprite_to_collider(bound_size, sprite_size), Color{100, 100, 100, 100});
    } else {
        animation.draw_frame(get_position() + Helper::adjust_sprite_to_collider(bound_size, sprite_size));
    }
}

void Crab::touch(const Object* from) {
    //add hurt() for rolling pin
}

void Crab::die() {
    current_game->remove_object(this);
}

void Crab::hurt(int amount) {
    health -= amount;
    flash_time = 0.1f;
    if (health <= 0) {
        die();
    }
}
