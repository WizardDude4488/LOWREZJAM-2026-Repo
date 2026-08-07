#pragma once

#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Weapon.hpp"
#include "Helper.hpp"

class RollingPin : public Weapon {
protected:
    static const std::string class_name;

    int offset_frame = 0;
    int animation_frame = 0;
    //static const std::vector<int> attack_frames;
    std::vector<int> attack_frames;

public:
    RollingPin(const std::string& n, int melee_dmg, Vector2 Pos);

    void draw() override;
    void touch(const Object* from) override;
    void update(float dt) override;

    const std::string& get_class() const override;

//draw needs override
//touch needs override
//update needs override
//get_class() needs override
};