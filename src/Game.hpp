#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "raylib.h"

#include "Object.hpp"

class Game {
protected:
    std::vector<Object*> objects;
    Object* player_object;
    Object* tilemap_object;
    float dt;

    RenderTexture2D canvas;
public:
    Game();

    void update();
    void draw();

    // Get and return last deltatime
    float get_dt();
    void update_dt(); // Modify this to allow time dilation
    // Call player method

    void add_object(Object* obj); // Use std::make_shared<Object> to add object to Game

    int find_object(const std::string& name); // Return index of object

    Object* get_object(const std::string& name);
    Object* get_object(int index);

    void remove_object(int index);
};