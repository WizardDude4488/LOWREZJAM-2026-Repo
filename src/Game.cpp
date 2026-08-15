#include <string>
#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

#include "raylib.h"

#include "Game.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "monsters/Crab.hpp"

#define LAYER_COUNT 7 // See Object.hpp for layer assignments

Game* current_game;

void begin_game() {
    current_game = new Game;
}
void end_game() {
    delete current_game;
}

Game::Game() {
    canvas = LoadRenderTexture(64, 64); // Create 64 x 64 canvas
    player_object = nullptr;
    collision_object = nullptr;
    dt = 0.0;
    current_layer = 0;
    current_track = nullptr;

    // create default image

    Image def = GenImageChecked(8, 8, 4, 4, MAGENTA, BLACK);

    textures["default"] = LoadTextureFromImage(def);
    UnloadImage(def);
}

Game::~Game() {
    for (Object* obj : objects) {
        delete obj;
    }

    for (const auto& text : textures) {
        UnloadTexture(text.second);
    }

    // Now that we have sound, make sure to delete them

    for (const auto& snd : sounds) {
        UnloadSound(snd.second);
    }

    for (const auto& msc : tracks) {
        UnloadMusicStream(msc.second);
    }

}

void Game::__unload_level() {
    if (level != nullptr) {

        if (player_object != nullptr) {
            level->player_position = player_object->get_position();
        }
    }
    // No longer owns these objects -- just drop references to them
    objects.clear();
    //player_object = nullptr;
    // Don't get rid of player; player object stays the same in all games
    collision_object = nullptr;
    // Don't unload assets
}

void Game::__load_level(Room* level) {
    // Unload current level (just clears references, doesn't delete)
    __unload_level();

    this->level = level;

    // Reference the level's objects directly; no copying needed since we don't own them
    collision_object = level->collision_object;

    if (player_object != nullptr) {
        player_object->set_position(level->player_position);
        objects.push_back(player_object);
        //std::cout << "Added player object to level 2" << std::endl;
    }

    if (collision_object != nullptr) {
        objects.push_back(collision_object);
        //std::cout << "Added collision object to level 2" << std::endl;
    }

    // Add other objects, excluding player and collision
    for (Object* object : level->objects) {

        if (object == nullptr) { continue; } // Skip invalid objects

        // Skip if this is the same object as player_object or collision_object
        // (avoid adding it twice, since it may already be in level->objects too)
        if (object == player_object) { continue; }
        if (object == collision_object) { continue; }

        objects.push_back(object);
        //std::cout << object->get_class() << std::endl;
    }
}

void Game::switch_level(Room* level) {
    command_queue.push_back(
        GameQueueCommand{GameQueueCommand::SWITCH_LEVEL, level}
    );
}

// Not using this anymore
/*

void Game::delete_level() {
    // Pretty much the same as the deconstructor
    for (Object* obj : objects) {
        delete obj;
    }
    // Ensure that pointers are invalidated
    player_object = nullptr;
    collision_object = nullptr;
    // Don't unload assets
}


void Game::copy_level(Room* level) {
    // Unload current level
    __unload_level();
    
    // Copy values; don't move
    // This becomes a little more complicated than using the copy constructor because
    // we need to make new pointers for collision_object and player_object
    Player* new_player_object = (level->player_object != nullptr) ? new Player(*(level->player_object)) : nullptr; // Change from Object* to Player* when impl.
    Tilemap* new_collision_object = (level->collision_object != nullptr) ? new Tilemap(*(level->collision_object)) : nullptr;

    if (new_player_object != nullptr) {
        objects.push_back(new_player_object);
    }
    
    if (new_collision_object != nullptr) {
        objects.push_back(new_collision_object); // Add to vectors
    }

    player_object = new_player_object;
    collision_object = new_collision_object;

    // Add other objects, excluding player and collision
    for (Object* object : level->objects) {

        if (object == nullptr) { continue; } // Skip invalid objects

        Player* try_player = (object->get_class() == "Player") ? static_cast<Player*>(object) : nullptr;
        Tilemap* try_collision = (object->get_class() == "Tilemap") ? static_cast<Tilemap*>(object) : nullptr;

        // NOTE: should add nullptr check everywhere player_object and collision_object is referenced
        if (try_player != nullptr && player_object != nullptr) {
            if (try_player == player_object) {
                continue; // Don't add the same player object twice, and don't add a nullptr object
            }
        }

        if (try_collision != nullptr && collision_object != nullptr) {
            if (try_collision == collision_object) {
                continue;
            }
        }

        // If duplication checks passed, add the object
        std::string obj_class = object->get_class();
        // Add new condition for each derived class we add
        if (obj_class == "Player") {
            Player* copy = new Player(*(static_cast<Player*>(object)));
            objects.push_back(copy); // Copy
        }
        else if (obj_class == "Tilemap") {
            Tilemap* copy = new Tilemap(*(static_cast<Tilemap*>(object)));
            objects.push_back(copy);
        }
    }
}

*/

void Game::update() {
    update_dt();

    for (Object* obj : objects) {
        obj->update(dt);
    }
}

void Game::reset() {
    // Reset first level
    first_level->objects.clear();
    //first_level->init();

    // Set player back to full health
    player_object->set_health(player_object->get_max_health());

    // Load level
    __load_level(first_level);
}

void Game::begin_draw() {
    BeginTextureMode(canvas);

    ClearBackground(BLACK);

    // Draw lowest objects first
    // So that objects with a lower draw_layer render underneath other objects
    for (int i = 0; i < LAYER_COUNT; i++) {
        for (Object* obj : objects) {
            if (obj->get_draw_layer() == i) {
                obj->draw();
            }
        }
    }
}

void Game::end_draw() {

    EndTextureMode();

    // Render canvas to screen
    BeginDrawing();

    ClearBackground(BLACK);

    Rectangle canvas_source_rect = { 0.0f, 0.0f, static_cast<float>(canvas.texture.width), static_cast<float>(canvas.texture.height) * -1.0f };

    float target_length = static_cast<float>(std::min(GetScreenWidth(), GetScreenHeight()));

    Vector2 window_size = { GetScreenWidth(), GetScreenHeight() };

    Rectangle canvas_target_rect;

    if (window_size.x >= window_size.y) {
        // Adjust on x axis
        canvas_target_rect = { (window_size.x - target_length) / 2.0f, 0.0f, target_length, target_length };
    }
    else {
        // Adjust on y axis
        canvas_target_rect = { 0.0f, (window_size.y - target_length) / 2.0f, target_length, target_length };
    }

    Vector2 position = { 0.0f, 0.0f };
    DrawTexturePro(canvas.texture, canvas_source_rect, canvas_target_rect, { 0.0f, 0.0f }, 0.0f, WHITE);

    EndDrawing();
}

float Game::get_dt() const {
    return dt;
}

void Game::update_dt() {
    dt = GetFrameTime();
}

void Game::add_object(Object* obj) {
    command_queue.push_back(
        GameQueueCommand{ GameQueueCommand::ADD_OBJ, obj }
    );
}

void Game::empty_queue() {
    for (GameQueueCommand command : command_queue) {
        // This because C++ is stupid
        Object* obj;
        Room* lvl;

        if (command.type == GameQueueCommand::ADD_OBJ) {
            obj = static_cast<Object*>(command.target);
            objects.reserve(objects.size() + 1);
            objects.insert(objects.end(), obj);
        } else if (command.type == GameQueueCommand::DEL_OBJ) {
            obj = static_cast<Object*>(command.target);
            auto at = std::find(objects.begin(), objects.end(), obj);
            if (at != objects.end()) {
                delete* at;
                objects.erase(at);
            }
        } else if (command.type == GameQueueCommand::SWITCH_LEVEL) {
            lvl = static_cast<Room*>(command.target);
            this->__load_level(lvl);
        }
        
        command_queue.clear();

        /* auto at = std::find(objects.begin(), objects.end(), obj);

        if (at != objects.end()) {
             delete *at;
             objects.erase(at);
        } */
    }
}

int Game::find_object(const std::string& name) const {
    for (int i = 0; i < objects.size(); i++) {
        Object* obj = objects.at(i);
        if (obj->get_name() == name) {
            return i;
        }
    }
    return -1;
}

Object* Game::get_object(const std::string& name) const {
    for (int i = 0; i < objects.size(); i++) {
        Object* obj = objects.at(i);
        if (obj->get_name() == name) {
            return obj;
        }
    }
    NullObject* nullobj = new NullObject("NullObject");
    return nullobj;  // If no object found
}

Player* Game::get_player_object() const { return player_object; }
Tilemap* Game::get_collision_object() const { return collision_object; }

int Game::get_current_layer() const {
    return current_layer;
}


void Game::remove_object(int index) {
    remove_object(objects.at(index));
}

void Game::remove_object(Object* obj) {
    command_queue.push_back(
        GameQueueCommand{ GameQueueCommand::DEL_OBJ, static_cast<void*>(obj) }
    );
}

void Game::load_image(const std::string& hash, const std::string& local_path) {
    std::string path = "assets/img/" + local_path;
    textures[hash] = LoadTexture(path.c_str());
}

void Game::load_image_from_rect(const std::string& hash, const std::string& local_path, const Rectangle& rect) {
    std::string path = "assets/img/" + local_path;
    Image img = LoadImage(path.c_str());

    Image img_rect = ImageFromImage(img, rect);

    textures[hash] = LoadTextureFromImage(img_rect);

    UnloadImage(img);
    UnloadImage(img_rect);
}

// TODO: add hash checking so we don't return a nonexistant hash
Texture2D Game::get_texture(const std::string& hash) const {
    if (textures.find(hash) != textures.end()) {
        return textures.at(hash);
    } else {
        return textures.at("default");
    }
    
}

void Game::load_sound(const std::string& hash, const std::string& local_path) {
    std::string path = "assets/snd/" + local_path;
    sounds[hash] = LoadSound(path.c_str());
}

void Game::set_sound_volume(float amount) {
    for (const auto& snd : sounds) {
        SetSoundVolume(snd.second, amount);
    }
}

Sound Game::get_sound(const std::string& hash) {
    return sounds[hash];
}

void Game::load_track(const std::string& hash, const std::string& local_path) {
    std::string path = "assets/msc/" + local_path;
    tracks[hash] = LoadMusicStream(path.c_str());
}

void Game::set_track_volume(float amount) {
    for (const auto& msc : tracks) {
        SetMusicVolume(msc.second, amount);
    }
}

void Game::set_current_track(const std::string& hash) {
    // If a track is already playing
    if (current_track != nullptr) {
        // Stop it
        StopMusicStream(*current_track);
    }
    if (hash != "none") {
        current_track = &tracks[hash];
        PlayMusicStream(*current_track);
        UpdateMusicStream(*current_track); // Make sure to load new data
    }
    else {
        current_track = nullptr;
    }
    
}

void Game::update_current_track() {
    if (current_track) {
        UpdateMusicStream(*current_track);
    }
}

Music* Game::get_current_track() { return current_track; }

Music Game::get_track(const std::string& hash) {
    return tracks[hash];
}

void Game::set_tile(int index, const std::string& texture) {
    tiles[index] = texture;
}

std::string Game::get_tile(int index) const {
    if (tiles.find(index) != tiles.end()) {
        return tiles.at(index);
    } else {
        return "default";
    }
}

std::vector<Object*> Game::get_list() {
    return std::vector<Object*>(objects);
}