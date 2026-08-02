#include <string>
#include <memory>
#include <algorithm>
#include <cstring>

#include "raylib.h"

#include "Game.hpp"
#include "Object.hpp"
#include "NullObject.hpp"

#define LAYER_COUNT 3

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
    // Pretty much the same as the deconstructor
    for (Object* obj : objects) {
        delete obj;
    }
    // Ensure that pointers are invalidated
    player_object = nullptr;
    collision_object = nullptr;
    // Don't unload assets
}


void Game::load_level(Level* level) {
    // Unload current level
    unload_level();
    
    // Copy values; don't move
    // This becomes a little more complicated than using the copy constructor because
    // we need to make new pointers for collision_object and player_object
    NullObject* new_player_object = new NullObject(*(level->player_object)); // Change from Object* to Player* when impl.
    Tilemap* new_collision_object = new Tilemap(*(level->collision_object));

    objects.push_back(new_player_object);
    objects.push_back(new_collision_object); // Add to vectors

    player_object = new_player_object;
    collision_object = new_collision_object;

    // Add other objects, excluding player and collision
    for (Object* object : level->objects) {

        if (object == nullptr) { break; } // Skip invalid objects

        NullObject* try_player = (object->get_class() == "NullObject") ? static_cast<NullObject*>(object) : nullptr;
        Tilemap* try_collision = (object->get_class() == "Tilemap") ? static_cast<Tilemap*>(object) : nullptr;

        if (try_player != nullptr) {
            // Maybe add a proper compare function if / when player is implemented
            if (std::memcmp(try_player, player_object, sizeof(NullObject))) { // Change to Player later
                break; // Don't add the same player object twice
            }
        }

        if (try_collision != nullptr) {
            if (std::memcmp(try_collision, collision_object, sizeof(Tilemap))) {
                break;
            }
        }

        // If duplication checks passed, add the object
        std::string obj_class = object->get_class();
        // Add new condition for each derived class we add
        if (obj_class == "NullObject") {
            NullObject* copy = new NullObject(*(static_cast<NullObject*>(object)));
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
    objects.push_back(obj);
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

int Game::get_current_layer() const {
    return current_layer;
}


void Game::remove_object(int index) {
    try {
        delete objects.at(index); // Deallocate
        objects.erase(objects.begin() + index); // Delete pointer
    }
    catch (...) {
        return;
    }
}

void Game::load_image(const std::string& hash, const std::string& local_path) {
    std::string path = "assets/" + local_path;
    textures[hash] = LoadTexture(path.c_str());
}

Texture2D Game::get_texture(const std::string& hash) const {
    return textures.at(hash);
}

void Game::set_tile(int index, const std::string& texture) {
    tiles[index] = texture;
}

const std::string& Game::get_tile(int index) const {
    return tiles.at(index);
}