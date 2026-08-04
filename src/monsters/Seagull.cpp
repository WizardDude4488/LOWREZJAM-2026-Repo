#include <iostream>
#include <vector>

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Game.hpp"
#include "Helper.hpp"
#include "Seagull.hpp"

using namespace Helper;

const std::string Seagull::class_name = "Seagull";

const std::string& Seagull::get_class() const {
    return class_name;
}

Seagull::Seagull(const std::string& n, Vector2 perch_pos, float radius) {
    name = n;
    draw_layer = 3;
    perch_position = perch_pos;
    target_position = perch_position;
    target_radius = radius;
    bounds = {perch_pos.x, perch_pos.y, 6, 6};
    animation = Animation("seagull", create_spritesheet_frames(6, 6, 64, 64, 1));
    health = 10;
    max_health = health;
}


void Seagull::update (float dt) {
    if (current_state == IDLE) {
        state_time += dt; // Only increment when IDLE
        if (state_time >= 3.0f) {
            // If the player is nearby, switch to swooping state to attack
            if (Vector2Distance(get_position(), current_game->get_player_object()->get_position()) <= target_radius) {
                current_state = DIVE;
                target_position = current_game->get_player_object()->get_position();
                state_time = 0.0f;
            }
        }
    } else if (current_state == DIVE) {
        direction = Vector2Normalize(target_position - get_position());
        Vector2 delta = Vector2Scale(direction, dt * speed); // Calculate speed
        // Same strategy as in Crab
        if (Vector2Distance(delta + get_position(), target_position) > Vector2Distance(get_position(), target_position)) {
            set_position(target_position); // Teleport
        }
        else {
            set_position(delta + get_position()); // Don't; Just move normally
        }

        // If we reached target, switch state
        if (get_position() == target_position) {
            current_state = PERCH;
            target_position = perch_position;
            state_time = 0.0f;
        }
    } else if (current_state == PERCH) {

        // TODO: this is pretty much just duplicating code, condense it
        direction = Vector2Normalize(target_position - get_position());
        Vector2 delta = Vector2Scale(direction, dt * speed); // Calculate speed

        if (Vector2Distance(delta + get_position(), target_position) > Vector2Distance(get_position(), target_position)) {
            set_position(target_position); // Teleport
        }
        else {
            set_position(delta + get_position()); // Don't; Just move normally
        }

        // If we reached target, switch state
        if (get_position() == target_position) {
            current_state = IDLE;
            target_position = perch_position;
            state_time = 0.0f;
        }
    }


    //could have separate while loop for hover animation if needed

    while (anim_time >= 1 / speed) {
        animation.set_frame((animation.get_frame() + 1) % 1);
    }

}

void Seagull::draw() {
    animation.draw_frame(get_position());
}

void Seagull::touch(const Object* from) {
    return;
}

void Seagull::die() {
    return;
}

void Seagull::hurt(int amount) {
    return;
}