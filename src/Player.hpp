#pragma once

#include "raylib.h"

#include "Character.hpp"

#include <vector>

class Player : public Character {
protected:
    static const std::string class_name;

    float speed;


public:

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