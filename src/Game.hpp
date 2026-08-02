#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "raylib.h"

#include "Object.hpp"

class Game {
protected:
    // Objects
    std::vector<Object*> objects;
    Object* player_object;
    Object* tilemap_object;
    float dt;

    // Assets
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<int, std::string> tiles;

    // Rendering
    RenderTexture2D canvas;
    int current_layer = 0;
public:
    Game();
    ~Game();

    void update();
    void draw();

    // Get and return last deltatime
    float get_dt() const;
    void update_dt(); // --Modify this to allow time dilation-- dont
    // --Call player method-- dont

    void add_object(Object* obj); // Use std::make_shared<Object> to add object to Game

    int find_object(const std::string& name) const; // Return index of object

    Object* get_object(const std::string& name) const;
    Object* get_object(int index) const;

    int get_current_layer() const;

    void remove_object(int index);

    void load_image(const std::string& hash, const std::string& local_path);
    Texture2D get_image(const std::string& hash) const;

    void set_tile(int index, const std::string& texture);
    const std::string& get_tile(int index) const;
};