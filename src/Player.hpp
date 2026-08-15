#pragma once

#include <string>

#include <vector>

#include <unordered_map>

#include "raylib.h"

#include "raymath.h"

#include "Animation.hpp"

#include "Character.hpp"


class Player : public Character {
protected:
    static const std::string class_name;

    const Vector2 sprite_size = { 13.0f, 13.0f };
    const Vector2 bound_size = { 13.0f, 13.0f };

    float speed = 15.0f;
    float hurt_time = 0.0f;

    float anim_time = 0.0f;
    int anim_counter = 0;
    
    enum Direction {RIGHT = 0, FORWARD = 21, LEFT = 42, BACKWARD = 63};
    Direction anim_direction = RIGHT;

    enum State {IDLE = 0, WALK = 6, ATTACK = 18};
    State anim_state = IDLE;
    State last_anim_state = IDLE;

    bool door_lock = false;

    //using an unordered map to with key type string and value type bool to track inventory
    std::unordered_map<std::string, int> inventory;
    

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
    
    //needs to be non-const so player can modify item's state
    //void pickup_weapon(Entity* from);
    void add_item(const Object* from);

    void set_health(int amount);
};