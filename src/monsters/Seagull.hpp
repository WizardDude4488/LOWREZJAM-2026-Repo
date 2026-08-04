#pragma once

#include <vector>
#include <string>

#include "raylib.h"

#include "Character.hpp" 

class Seagull : public Character {
protected:
    static const std::string class_name;

    float speed = 30.0f;
    float target_radius;
    float state_time = 0.0f;
    float anim_time = 0.0f;

    Vector2 perch_position;
    Vector2 target_position;

    Vector2 direction = { 0.0f, 0.0f };
    Vector2 velocity = { 0.0f, 0.0f };

    enum SeagullState { IDLE = 0, DIVE = 1, PERCH = 2 };
    SeagullState current_state = IDLE;

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