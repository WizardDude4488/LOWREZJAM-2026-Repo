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

    if (flip) {
        velocity.x = -0.5f;
    } else {
        velocity.x = 0.5f;
    }

    if (flip && bounds.x == 0) {
        flip = false;
    } 

    if (!flip && bounds.x == 56) {
        flip = true;
    }

    while (anim_time >= 0.1) {
        animation.set_frame((animation.get_frame() + 1) % 2);
        anim_time -= 0.25;
    }
}

void Crab::draw() {
    animation.draw_frame(get_position());
}

void Crab::touch(const Object* from) {
    std::vector<Object*> list = current_game->get_list();

    for (Object* i : list) {
        if (i->get_class() == "Player") {
            Player* player = static_cast<Player*>(i);
            if (CheckCollisionRecs(bounds, player->get_bounds())) {
                player->hurt(5);
            }
        }
    }
}

void Crab::die() {
    return;
}

void Crab::hurt(int amount) {
    return;
}