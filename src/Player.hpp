#pragma once

#include "Character.h"
#include "raylib.h"
#include <vector>

class Player : public Character {
protected:
    

public:
    void die() override;
    void move() override;



}
