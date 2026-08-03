#include <iostream>
#include <vector>

#include <string>

#include "raylib.h"
#include "raymath.h"

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

    int buffer = 2;

    if (dir.x == 0.0f && dir.y == 0.0f) {
        dir = Vector2Normalize(Vector2Subtract(point2, point1));
    }

    
    velocity = Vector2Scale(dir, speed);

    Vector2 delta = {0.0f, 0.0f};
    delta = Vector2Scale(velocity, dt);

    std::cout << "\n" << Vector2Distance(get_position(), point2);

    set_position(delta + get_position());

    if (Vector2Distance(get_position(), point1) <= buffer && 
        (dir.x < Vector2Normalize(Vector2Subtract(point2, point1)).x ||
         dir.y < Vector2Normalize(Vector2Subtract(point2, point1)).y)) {
        set_position(point1);
        dir.x = -dir.x;
        dir.y = -dir.y;
        std::cout << "\nFlip";
    } else if (Vector2Distance(get_position(), point2) <= buffer && 
        (dir.x > Vector2Normalize(Vector2Subtract(point1, point2)).x ||
         dir.y > Vector2Normalize(Vector2Subtract(point1, point2)).y)) {
        set_position(point2);
        dir.x = -dir.x;
        dir.y = -dir.y;
        std::cout << "\nFlip";
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
    return;
}

void Crab::die() {
    return;
}

void Crab::hurt(int amount) {
    return;
}