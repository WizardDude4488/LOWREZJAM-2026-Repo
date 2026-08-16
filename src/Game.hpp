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
#include "Level.hpp"

// NOTE TO SELF: Don't include Game.hpp in other .hpp files unless it needs it. This can cause circular dependencies.

extern Game* current_game;

void begin_game();
void end_game();

struct GameQueueCommand {
    enum QueueCommandType { ADD_OBJ, DEL_OBJ, SWITCH_LEVEL, RESET };
    QueueCommandType type;
    // If ADD_OBJ or DEL_OBJ, then void* is Object*; If SWITCH_LEVEL, then void* Room*
    void* target;
};

class Game {
protected:
    // Objects
    std::vector<Object*> objects;

    std::vector<GameQueueCommand> command_queue;
    Tilemap* collision_object; // Current layer considered for wall collision
    float dt;

    // Assets
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<int, std::string> tiles;

    std::unordered_map<std::string, Sound> sounds;

    std::unordered_map<std::string, Music> tracks;
    Music* current_track;

    // Rendering
    std::unordered_map<std::string, Shader> shaders;

    RenderTexture2D canvas;
    int current_layer = 0;
public:
    Player* player_object;

    Room* current_room = nullptr;
    Level* current_level = nullptr;
    Room* first_level = nullptr;

    Game();
    ~Game();

    //void delete_level(); // Room in locally stored memory, not other level
                         // Should not be called when loading a level using load_level
                         // Use copy_level instead
    //void copy_level(Room* level); // Need to explicitly call delete_level afterwards (IF NEEDED)

    void __unload_room();
    void __load_room(Room* room);

    void switch_room(Room* room);

    void update();
    //void draw();
    void reset(); // Called if player dies

    void begin_draw(); // Draw to canvas
    void end_draw(); // Finalize, draw to screen

    // Get and return last deltatime
    float get_dt() const;
    void update_dt(); // --Modify this to allow time dilation-- dont
    // --Call player method-- dont

    void add_object(Object* obj); // Use std::make_shared<Object> to add object to Game
    void empty_queue();

    int find_object(const std::string& name) const; // Return index of object

    Object* get_object(const std::string& name) const;
    Object* get_object(int index) const;

    Player* get_player_object() const; // Change to Player* later
    Tilemap* get_collision_object() const;

    int get_current_layer() const;

    void remove_object(int index);
    void remove_object(Object* obj);

    void load_image(const std::string& hash, const std::string& local_path);
    void load_image_from_rect(const std::string& hash, const std::string& local_path, const Rectangle& rect);
    Texture2D get_texture(const std::string& hash) const;

    void load_sound(const std::string& hash, const std::string& local_path);
    void set_sound_volume(float amount);
    Sound get_sound(const std::string& hash);

    void load_track(const std::string& hash, const std::string& local_path);
    void set_track_volume(float amount);

    void set_current_track(const std::string& hash);
    void update_current_track();
    Music* get_current_track();
    Music get_track(const std::string& hash);

    void set_tile(int index, const std::string& texture);
    std::string get_tile(int index) const;

    std::vector<Object*> get_list();
};