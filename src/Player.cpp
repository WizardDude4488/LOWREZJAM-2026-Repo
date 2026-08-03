#include <iostream>

#include "raylib.h"

#include "Player.hpp"
#include "Helper.hpp"
using namespace Helper;

Player::Player(const std::string& n) {

    name = n;
    draw_layer = 4;
    bounds = {0, 0, 8, 8};
    animation = Animation("yellow-guy", create_spritesheet_frames(5, 8, 64, 64, 4));
    max_health = 20;
    health = max_health;
}

const std::string Player::class_name = "Player";

// From Object.hpp

const std::string& Player::get_class() const {
    return class_name;
}

void Player::update(float dt) {

    Vector2 direction = Vector2{0.0f, 0.0f};

    if (IsKeyDown(KEY_A)) { velocity.x -= 1; }
    if (IsKeyDown(KEY_D)) { velocity.x += 1; }
    if (IsKeyDown(KEY_W)) { velocity.y -= 1; }
    if (IsKeyDown(KEY_S)) { velocity.y += 1; }

    direction = Vector2Normalize(direction);
    direction = Vector2Scale(direction, speed);

    velocity += direction;

    Vector2 delta = {0.0f, 0.0f};

    delta.x = get_position().x + velocity.x*dt;
    delta.y = get_position().y + velocity.y*dt;

    set_position(delta);

    // Add friction
    velocity = Vector2Scale(velocity, 0.8f);

    anim_time += dt;
    
    while (anim_time >= 0.1) {
        animation.set_frame((animation.get_frame() + 1) % 4);
        anim_time -= 0.25;
    }
}

// TODO: draw animation object here
void Player::draw() {
    animation.draw_frame(get_position());
}

// TODO: hurt player when something like an enemy or spike calls this function
void Player::touch(const Object* from) {

}

void Player::die() {
    
    /* // Redundant to check health here
    if (health <= 0) {
        [...]
    }
    */

    //code for death sequence/animation, maybe a "You Died" screen
    //sets player back to last checkpoint or smth

}

void Player::hurt(int amount) {
    health -= amount;

    if (health <= 0) {
        die();
    } else {
        // Play hurt animation
    }
}