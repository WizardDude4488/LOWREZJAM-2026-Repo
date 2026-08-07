#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Helper.hpp"
#include "Weapon.hpp"
#include "Game.hpp"

static const std::string class_name = "Weapon";

const std::string& Weapon::get_class() const {
    return class_name;
}

Weapon::Weapon(std::string& n, int melee_dmg, Vector2 position) {
    name = n;
    melee_damage = melee_dmg;
    pos = position;
}


//not using touch directly since that would conflict with return type of method in Object.hpp
Weapon* Weapon::pickup() {
    held = true;
    return this;
}

WeaponState Weapon::get_state() const {
    return current_state;
}

WeaponDirection Weapon::get_weapon_direction() const {
    return current_direction;
}

bool Weapon::is_held() {
    return held;
}

void Weapon::drop() {
        Vector2 final_pos = {0, 0};
        final_pos.x = (current_game->get_player_object())->get_position().x + 10;
        final_pos.y = (current_game->get_player_object())->get_position().y + 10;
        //will be at a location slightly outside player so they don't pick it up again immediately (for testing purposes)
        held = false;
}

void Weapon::touch(const Object* from) {
    return;
}

void Weapon::update(float dt) {
    return;
}

void Weapon::draw() {
    return;
}