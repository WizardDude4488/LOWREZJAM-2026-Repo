#pragma once

#include <vector>
#include <string>

#include "raylib.h"

#include "Character.hpp" 

class Seagull : public Character {
protected:
    static const std::string class_name;

    float speed = 300.0f;
    float anim_time = 0.0f;

    Vector2 velocity = {0.0f, 0.0f};
    Vector2 dive_path = {0.0f, 0.0f};
    Vector2 endpoint = {0.0f, 0.0f};
    Vector2 dir = {0.0f, 0.0f};

    bool x_flipped = false;
    bool y_flipped = false;

    bool hover = false;
    bool dive = false;

    float hover_time = 0.0f;

public:
    Seagull(const std::string& n, Vector2 Pos);

    const std::string& get_class() const override;
    void update(float dt) override;
    void draw() override;

    // From Entity.hpp
    void touch(const Object* from) override;

    // From Character.hpp
    void die() override;
    void hurt(int amount) override;

};