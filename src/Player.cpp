#include <iostream>

#include "raylib.h"

#include "Game.hpp"
#include "Player.hpp"
#include "Helper.hpp"
using namespace Helper;

Player::Player(const std::string& n, Vector2 Pos) {

    name = n;
    draw_layer = 4;
    bounds = {Pos.x, Pos.y, 5, 8};
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

    // Set intended position

    delta = get_position() + Vector2Scale( velocity, dt );

    set_position(delta);

    // Calculate collision; try on each axis (TODO: Move this functionality into calculate_tile_collision)

    // X first
    Vector2 collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
    bounds.x = collision.x;

    // Then Y
    collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
    bounds.y = collision.y;

    // Add friction
    velocity = Vector2Scale(velocity, 0.8f);

    anim_time += dt;
    
    while (anim_time >= 0.1) {
        animation.set_frame((animation.get_frame() + 1) % 4);
        anim_time -= 0.25;
    }

    hurt_time -= dt;

    // Handle player hurt
    if (hurt_time <= 0.0f) {
        if (IsKeyDown(KEY_X)) { hurt(10); }
    }

    //using weapons
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (current_weapon != nullptr) {
            //need to return pointer to weapon so draw layer, position, etc. can be modified based on player status
            current_weapon.use(this);
        }
    }
}

// TODO: draw animation object here
void Player::draw() {
    animation.draw_frame(get_position());

    // Draw rectangle for health bar
    DrawRectangle(0, 0, get_health(), 5, RED);
}

// TODO: hurt player when something like an enemy or spike calls this function
void Player::touch(const Object* from) {
    if (from->get_class() == "Crab") {
        hurt(5); // Set damage from each class
    }
    if (from->get_class() == "Weappon") {
        if (!from->is_held()) {
            //change current_weapon to weapon being picked up
            current_weapon = from->pickup();
        }
    }
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
    
    // ONLY hurt if not in i frame
    if (hurt_time <= 0.0f) {
        health -= amount;
        hurt_time = 5.0f; // Wait 5 seconds before being able to be hurt again
    }

    if (health <= 0) {
        die();
    } else {
        // Play hurt animation
    }
}