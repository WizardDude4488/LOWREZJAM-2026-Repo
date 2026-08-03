#include <iostream>
#include <vector>

#include <string>

#include "raylib.h"

#include "Game.hpp"
#include "Helper.hpp"
#include "Crab.hpp"

using namespace Helper;


Crab::Crab(const std::string& n, Vector2 Pos) {
    name = n;
    draw_layer = 3;
    bounds = {Pos.x, Pos.y, 8, 8};
    animation = Animation("crab", create_spritesheet_frames(10, 8, 64, 64, 2));
    max_health = 20;
    health = max_health;

}

const std::string Crab::class_name = "Crab";

const std::string& Crab::get_class() const {
    return class_name;
}

void Crab::update(float dt) {

    Vector2 point1 = {0, 32};
    Vector2 point2 = {56, 32};

    if (dir.x == 0.0f && dir.y == 0.0f) {
        dir = Vector2Normalize(point2 - point1);
    }

    if (get_position().x > point2.x) {
        dir = Vector2Normalize(point1 - point2);
        std::cout << "\nLeft";
    } else if (get_position().x < point1.x + 1) {
        dir = Vector2Normalize(point2 - point1);
        std::cout << "\nRight";
    }
    
    velocity = Vector2Scale(dir, speed);

    Vector2 delta = {0.0f, 0.0f};
    delta = Vector2Scale(velocity, dt);

    std::cout << "\n" << velocity.x;

    set_position(delta + get_position());

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
    return;
}

void Crab::die() {
    return;
}

void Crab::hurt(int amount) {
    return;
}