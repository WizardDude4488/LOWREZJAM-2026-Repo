#pragma once

#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Entity.hpp"

class Item : public Entity {
protected:
    //location
public:
    //change get_class to be here so player class checking is easier

    //need to override touch here since it will work the same for all derived ingredients
    void touch(const Object* from) override;
    //void touch2();

    //don't implement draw or update here since those depend on an animation object which needs 
    //animation frames specific to each item, not the general item class

    //using a virtual destructor
    virtual ~Item() = default;

};