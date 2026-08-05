#pragma once

#include <string>

#include <vector>

#include "raylib.h"

#include "raymath.h"

#include "Animation.hpp"

#include "Character.hpp"

#include "Weapon.hpp"


class Player : public Character {
protected:
    static const std::string class_name;

    float speed = 10.0f;
    float anim_time = 0.0f;
    float hurt_time = 0.0f;

    Vector2 velocity = {0.0f, 0.0f};

    Weapon* current_weapon = nullptr;


public:
    Player(const std::string& n, Vector2 Pos);

    // From Object.hpp
    const std::string& get_class() const override;
    void update(float dt) override;
    void draw() override;

    // From Entity.hpp
    void touch(const Object* from) override;

    // From Character.hpp
    void die() override;
    void hurt(int amount) override;

};