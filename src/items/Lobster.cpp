#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Helper.hpp"
#include "Animation.hpp"

#include "Lobster.hpp"

using namespace Helper;

//need to have specific class names for each item, since this will be used for updating player inventory
const std::string Lobster::class_name = "Lobster";

const std::string& Lobster::get_class() const {
    return class_name;
}

Lobster::Lobster(const std::string& n, Vector2 Pos) {
    name = n;
    draw_layer = 5; 
    bounds = {Pos.x, Pos.y, 11, 14};
    animation = Animation("lobster", create_spritesheet_frames(11, 14, 11, 42, 3));
    
}

void Lobster::update(float dt) {
    anim_time += dt;

    while(anim_time >= 0.2) {
        animation.set_frame((animation.get_frame() + 1) % 3);
        anim_time = 0;
    }
}

void Lobster::draw() {
    animation.draw_frame(get_position());
}

