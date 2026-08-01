#include <string>
#include <memory>
#include <algorithm>

#include "Game.hpp"
#include "Object.hpp"
#include "NullObject.hpp"

#define LAYER_COUNT 3

Game::Game() {
    canvas = LoadRenderTexture(64, 64); // Create 64 x 64 canvas
    player_object = nullptr;
    tilemap_object = nullptr;
    dt = 0.0;
}

void Game::update() {
    for (Object* obj : objects) {
        obj->update(this, dt);
    }
}

void Game::draw() {
    // Render to 64 x 64 canvas
    BeginTextureMode(canvas);
    // Draw lowest objects first
    // So that objects with a lower draw_layer render underneath other objects
    for (int i = 0; i < 3; i++) {
        for (Object* obj : objects) {
            if (obj->get_draw_layer() == i) {
                obj->draw(this);
            } 
        }
    }

    EndTextureMode();

    // Render canvas to screen
    BeginDrawing();

    Rectangle canvas_source_rect = { 0.0f, 0.0f, static_cast<float>(canvas.texture.width), static_cast<float>(canvas.texture.height) * -1.0 };

    float target_length = static_cast<float>(std::min(GetScreenWidth(), GetScreenHeight()));

    Rectangle canvas_target_rect = { 0.0f, 0.0f, target_length, target_length };

    Vector2 position = { 0.0f, 0.0f };
    DrawTexturePro(canvas.texture, canvas_source_rect, canvas_target_rect, {0.0f, 0.0f}, 0.0f, WHITE);

    EndDrawing();
}

void Game::add_object(Object* obj) {
    objects.push_back(obj);
}

int Game::find_object(const std::string& name) {
    for (int i = 0; i < objects.size(); i++) {
        Object* obj = objects.at(i);
        if (obj->get_name() == name) {
            return i;
        }
    }
    return -1;
}

Object* Game::get_object(const std::string& name) {
    for (int i = 0; i < objects.size(); i++) {
        Object* obj = objects.at(i);
        if (obj->get_name() == name) {
            return obj;
        }
    }
    NullObject* nullobj = new NullObject("NullObject");
    return nullobj;  // If no object found
}

void Game::remove_object(int index) {
    try {
        objects.erase(objects.begin() + index);
    }
    catch (...) {
        return;
    }
}