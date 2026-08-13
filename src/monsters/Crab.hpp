#pragma once

#include <vector>
#include <string>

#include "raylib.h"

#include "Character.hpp"

class Crab : public Character {
protected:
    static const std::string class_name;
    const Vector2 sprite_size = { 12.0f, 12.0f };
    const Vector2 bound_size = { 8.0f, 8.0f };

    float speed;
    float anim_time = 0.0f;
    int anim_counter = 0;

    Vector2 start_position;
    Vector2 end_position;

    Vector2 direction = { 0.0f, 0.0f };
    Vector2 velocity = { 0.0f, 0.0f };

    enum CrabState {TO_START = 0, TO_END = 1};
    CrabState current_state = TO_END;

    enum Direction { RIGHT = 5, FORWARD = 7, LEFT = 10, BACK = 7 };
    Direction anim_direction = FORWARD;

public:
    Crab(const std::string& n, Vector2 start_pos, Vector2 end_pos, float s);

    const std::string& get_class() const override;
    void update(float dt) override;
    void draw() override;

    // From Entity.hpp
    void touch(const Object* from) override;

    // From Character.hpp
    void die() override;
    void hurt(int amount) override;

};