#pragma once

#include "Character.h"
#include "raylib.h"
#include <vector>

class Player : public Character {
protected:
    float speed;
    

public:
    void die() override;
    void update(float dt) override;



}
