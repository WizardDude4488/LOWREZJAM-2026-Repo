#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "raylib.h"

#include "Object.hpp"
#include "Player.hpp"
#include "NullObject.hpp"
#include "Tilemap.hpp"

// NOTE TO SELF: Don't include Game.hpp in other .hpp files unless it needs it. This can cause circular dependencies.

extern Game* current_game;

void begin_game();
void end_game();

class Game {
protected:
    // Objects
    std::vector<Object*> objects;
    Player* player_object; // Change to Player* when Player is implemented
    Tilemap* collision_object; // Current layer considered for wall collision
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

    void unload_level();
    // Can only be implemented fully when Player is implemented
    void load_level(Level* level);

    void delete_level(); // Level in locally stored memory, not other level
                         // Should not be called when loading a level using load_level
                         // Use copy_level instead
    void copy_level(Level* level); // Need to explicitly call delete_level afterwards (IF NEEDED)

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

    Player* get_player_object() const; // Change to Player* later
    Player* get_player() const;
    Tilemap* get_collision_object() const;

    int get_current_layer() const;

    void remove_object(int index);

    void load_image(const std::string& hash, const std::string& local_path);
    Texture2D get_texture(const std::string& hash) const;

    void set_tile(int index, const std::string& texture);
    const std::string& get_tile(int index) const;

    std::vector<Object*> get_list();
};