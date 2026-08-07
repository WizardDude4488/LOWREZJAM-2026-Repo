#pragma once

#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Entity.hpp"
#include "Helper.hpp"

//defining enums, different weapons can have different states to switch between
enum WeaponState {READY = 0, ATTACKING = 1, COOLDOWN = 2, RELOAD = 3};
enum WeaponDirection {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

class Weapon : public Entity {
protected:
    float anim_time = 0.0f;

    int melee_damage;

    bool held = false;

    Vector2 pos = {0, 0};

    WeaponState current_state = READY;
    WeaponDirection current_direction = RIGHT;

public:
    Weapon() = default;
    Weapon(std::string& n, int melee_dmg, Vector2 position);

    const std::string& get_class() const override; //good

    WeaponState get_state() const;
    WeaponDirection get_weapon_direction() const;

    //change these
    Weapon* pickup(Entity* from);
    void drop(Entity* from);

    bool is_held();

    void touch(const Object* from) override; //good
    void update(float dt) override; //good
    void draw() override; //good

};