#include "raylib.h"

#include "Player.hpp"

const std::string Player::class_name = "Player";

// From Object.hpp

const std::string& Player::get_class() const {
    return class_name;
}

void Player::update(float dt) {
    int KEY_A = 65;
    int KEY_W = 87;
    int KEY_S = 83;
    int KEY_D = 68;


    if (IsKeyDown(KEY_A) &&
        !IsKeyDown(KEY_W) &&
        !IsKeyDown(KEY_S) &&
        !IsKeyDown(KEY_D)) {
            //decrement x by speed*dt

        
    };
}

// TODO: draw animation object here
void Player::draw() {
    return;
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