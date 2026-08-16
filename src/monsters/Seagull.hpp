#pragma once

#include <vector>
#include <string>

#include "raylib.h"

#include "Character.hpp" 

class Seagull : public Character {
protected:
    static const std::string class_name;
    const Vector2 sprite_size = { 11.0f, 11.0f };
    const Vector2 bound_size = { 5.0f, 5.0f };

    float speed = 30.0f;
    float target_radius;
    float state_time = 0.0f;

    float anim_time = 0.0f;
    int anim_counter = 0;

    Vector2 perch_position;
    Vector2 target_position;

    Vector2 direction = { 0.0f, 0.0f };
    Vector2 velocity = { 0.0f, 0.0f };

    enum Direction {LEFT = 8, RIGHT = 0};
    Direction anim_direction = RIGHT;

    // Dive and Perch use the same animations
    enum SeagullState { IDLE, DIVE, PERCH };
    SeagullState current_state = IDLE;

    enum SeagullAnimationState {SIT = 0, FLY = 3};
    SeagullAnimationState anim_state = SIT;

    float flash_time = 0.0f;

public:
    Seagull(const std::string& n, Vector2 perch_pos, float radius);

    const std::string& get_class() const override;
    void update(float dt) override;
    void draw() override;

    // From Entity.hpp
    void touch(const Object* from) override;

    // From Character.hpp
    void die() override;
    void hurt(int amount) override;
};