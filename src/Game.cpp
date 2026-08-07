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
}

void Game::unload_level() {
    // No longer owns these objects -- just drop references to them
    objects.clear();
    player_object = nullptr;
    collision_object = nullptr;
    // Don't unload assets
}

void Game::load_level(Level* level) {
    // Unload current level (just clears references, doesn't delete)
    unload_level();

    // Reference the level's objects directly; no copying needed since we don't own them
    player_object = level->player_object;
    collision_object = level->collision_object;

    if (player_object != nullptr) {
        objects.push_back(player_object);
    }

    if (collision_object != nullptr) {
        objects.push_back(collision_object);
    }

    // Add other objects, excluding player and collision
    for (Object* object : level->objects) {

        if (object == nullptr) { continue; } // Skip invalid objects

        // Skip if this is the same object as player_object or collision_object
        // (avoid adding it twice, since it may already be in level->objects too)
        if (object == player_object) { continue; }
        if (object == collision_object) { continue; }

        objects.push_back(object);
    }
}

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


void Game::copy_level(Level* level) {
    // Unload current level
    unload_level();
    
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


void Game::update() {
    update_dt();

    for (Object* obj : objects) {
        obj->update(dt);
    }
}

void Game::draw() {
    // Render to 64 x 64 canvas
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
    } else {
        // Adjust on y axis
        canvas_target_rect = { 0.0f, (window_size.y - target_length) / 2.0f, target_length, target_length };
    }

    Vector2 position = { 0.0f, 0.0f };
    DrawTexturePro(canvas.texture, canvas_source_rect, canvas_target_rect, {0.0f, 0.0f}, 0.0f, WHITE);

    EndDrawing();
}

float Game::get_dt() const {
    return dt;
}

void Game::update_dt() {
    dt = GetFrameTime();
}

void Game::add_object(Object* obj) {
    object_add_queue.push_back(obj);
}

void Game::empty_queue() {
    // Append new objects
    objects.reserve(objects.size() + object_add_queue.size());
    objects.insert(objects.end(), object_add_queue.begin(), object_add_queue.end());
    object_add_queue.clear();
    // Remove old objects
    for (Object* obj : object_remove_queue) {
        auto at = std::find(objects.begin(), objects.end(), obj);

        if (at != objects.end()) {
             delete *at;
             objects.erase(at);
        }
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
    object_remove_queue.push_back(objects.at(index));
}

void Game::remove_object(Object* obj) {
    object_remove_queue.push_back(obj);
}

void Game::load_image(const std::string& hash, const std::string& local_path) {
    std::string path = "assets/" + local_path;
    textures[hash] = LoadTexture(path.c_str());
}

void Game::load_image_from_rect(const std::string& hash, const std::string& local_path, const Rectangle& rect) {
    std::string path = "assets/" + local_path;
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