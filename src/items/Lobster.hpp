#pragma once

#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Item.hpp"

class Lobster : public Item {
protected:

    static const std::string class_name;
    float anim_time = 0.0f; 

public:
    const std::string& get_class() const override;

    Lobster(const std::string& n, Vector2 Pos);
    //only implementing update and draw here since touch are the same for all items on ground
    void update(float dt) override;
    void draw() override;
    

};