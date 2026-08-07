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
    bounds = {start_pos.x, start_pos.y, 8, 8};
    animation = Animation("crab", create_spritesheet_frames(10, 8, 64, 64, 2));
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

    while (anim_time >= 1 / speed) {
        animation.set_frame((animation.get_frame() + 1) % 2);
        anim_time = 0;
    }

    // Check for collision with player

    std::vector<Object*> list = current_game->get_list();

    for (Object* i : list) {
        if (i->get_class() == "Player") {
            Player* player = static_cast<Player*>(i);
            if (CheckCollisionRecs(bounds, player->get_bounds())) {
                player->touch(this);
            }
        }
    }

}

void Crab::draw() {
    animation.draw_frame(get_position());
}

void Crab::touch(const Object* from) {
    //add hurt() for rolling pin
    if (from->get_class() == "RollingPin") {
        hurt(5);
        std::cout << "\nCrab took five damage.";
    }
}

void Crab::die() {
    return;
}

void Crab::hurt(int amount) {
    return;
}
