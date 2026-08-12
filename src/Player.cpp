#include <iostream>

#include "raylib.h"

#include "Game.hpp"
#include "Player.hpp"
#include "Helper.hpp"
#include "Weapon.hpp"
#include "Door.hpp"

using namespace Helper;

Player::Player(const std::string& n, Vector2 Pos) {

    name = n;
    draw_layer = 5;
    bounds = {Pos.x, Pos.y, 13, 13};
    animation = Animation("player", create_spritesheet_frames(13, 13, 143, 143, 84));
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

    bool a = IsKeyDown(KEY_A);
    bool d = IsKeyDown(KEY_D);
    bool w = IsKeyDown(KEY_W);
    bool s = IsKeyDown(KEY_S);

    if (a) { direction.x -= 1; anim_direction = LEFT;        anim_state = WALK; }
    if (d) { direction.x += 1; anim_direction = RIGHT;       anim_state = WALK; }
    if (w) { direction.y -= 1; anim_direction = BACKWARD;    anim_state = WALK; }
    if (s) { direction.y += 1; anim_direction = FORWARD;     anim_state = WALK; }

    if (!(a || d || w || s)) {
        anim_state = IDLE;
    }

    Vector2 delta = Vector2Scale(Vector2Normalize(direction), speed * dt);

    // Set intended position

    set_position(get_position() + delta);

    // Calculate collision; try on each axis (TODO: Move this functionality into calculate_tile_collision)

    // X first
    Vector2 collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
    /*bounds.x = collision.x;

    // Then Y
    collision = Helper::calculate_tile_collision(get_bounds(), current_game->get_collision_object());
    bounds.y = collision.y; */

    set_position(collision);

    if (last_anim_state != anim_state) {
        anim_time = 0.0f;
        anim_counter = 0;
    }

    anim_time += dt;
    hurt_time -= dt;
    
    while (anim_time >= 0.2) {
        if (anim_state == IDLE) {
            anim_counter = (anim_counter + 1) % 6; // Idle animation has 6 frames
        } else if (anim_state == WALK) {
            anim_counter = (anim_counter + 1) % 12; // Walk animation has 12 frames
        } else if (anim_state == ATTACK) {
            anim_counter = (anim_counter + 1) % 3; // Attack animation has 3 frames
        }
        anim_time -= 0.2;
    }
    
    animation.set_frame(anim_direction + anim_state + anim_counter);

    last_anim_state = anim_state;

    // Handle player hurt
    if (hurt_time <= 0.0f) {
        if (IsKeyDown(KEY_X)) { hurt(10); }
    }

    //using weapons
    /*if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (current_weapon != nullptr) {
            //need to return pointer to weapon so draw layer, position, etc. can be modified based on player status
            current_weapon->use(this);
        }
    }*/

    std::vector<Object*> list = current_game->get_list();

    for (Object* i : list) {
        if (i->get_class() == "Door") {
            //std::cout << "Found door in object list." << std::endl;
            Door* door = static_cast<Door*>(i);
            if (CheckCollisionRecs(bounds, door->get_bounds())) {
                if (!door_lock) {
                    door_lock = true;
                    door->touch(this);
                    //std::cout << "Door touch called." << std::endl;
                }
            } else {
                door_lock = false;
            }
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
}

/*void Player::pickup_weapon(Entity* from) {
    if (from == nullptr) {
        return;
    } else if (from->get_class() == "Weapon") {
        Weapon* next_weapon = static_cast<Weapon*>(from);
        if (current_weapon != nullptr) {
            current_weapon->drop(this);
        }
        //change current_weapon to weapon being picked up
        current_weapon = next_weapon->pickup(this);
        std::cout << "\nPicked up weapon.";
    }
}*/

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


//implement an add_item method so items can change player inventory when their touch methods are called
void Player::add_item(const Object* from) {
    //check if the item associated with the class name already has an entry
    //if not, add it to the map with a value of true
    std::string item_name = from->get_class();
    if (inventory.find(item_name) != inventory.end()) {
        inventory.insert({item_name, true});
    }

}