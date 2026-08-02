#pragma once 

#include "raylib.h"
#include "Entity.h"
#include "Animation.h"
#include <vector>

class Character : public Entity {
protected:
    int max_health;
    int health;

public:
    
    //can modify return type later if we need a number, etc from one of these
    //for now, just modify class member variables
    virtual void die() = 0;
    virtual void hurt() = 0;

    int get_health();
    int get_max_health();

}