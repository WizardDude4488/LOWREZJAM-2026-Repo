#include <iostream>
#include <vector>

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Game.hpp"
#include "Helper.hpp"
#include "Seagull.hpp"

using namespace Helper;

const std::string Seagull::class_name = "Seagull";

const std::string& Seagull::get_class() const {
    return class_name;
}

Seagull::Seagull(const std::string& n, Vector2 Pos) {
    name = n;
    draw_layer = 3;
    bounds = {Pos.x, Pos.y, 6, 6};
    animation = Animation("seagull", create_spritesheet_frames(6, 6, 64, 64, 1));
    health = 10;
    max_health = health;

}


void Seagull::update (float dt) {
    std::cout << "Seagull: x: " << bounds.x << " y: " << bounds.y << "\n";
    if (dive) {
        //increment x and y
        //check if Pos = endpoint
        //if yes, dive = false

        Vector2 delta = Vector2Scale(velocity, dt);
        Vector2 new_pos = {0.0f, 0.0f};
        set_position(Vector2Add(delta, get_position()));

        
        if (x_flipped && y_flipped) { 
            if (get_position().x < endpoint.x || get_position().y < endpoint.y) {
            set_position(endpoint); 
            dive = false;
            //add hover = true into if statements if using separate frames for the hover animation
        }
        } else if (x_flipped && !y_flipped) {
            if (get_position().x < endpoint.x  || get_position().y > endpoint.y) {
            set_position(endpoint);
            dive = false;
        }
        } else if (!x_flipped && y_flipped) {
            if (get_position().x > endpoint.x  || get_position().y < endpoint.y) {
            set_position(endpoint);
            dive = false;
        }
        } else {
            if (get_position().x > endpoint.x  || get_position().y > endpoint.y) {
            set_position(endpoint);
            dive = false;
        }
        }
            
    } else {
            hover_time += dt;
    }

    if (hover_time >= 1.0) {
        //seagull targets player's position when called, flies toward during dive
        endpoint = current_game->get_player()->get_position();
        dive_path = Vector2Subtract(endpoint, get_position());

        if (dive_path.x < 0) {x_flipped = -1;}
        if (dive_path.y < 0) {y_flipped = -1;}

        dir = Vector2Normalize(dive_path);
        velocity = Vector2Scale(dir, speed);

        hover_time = 0;
        dive = true;
    }


    //could have separate while loop for hover animation if needed

    while (anim_time >= 1 / speed) {
        animation.set_frame((animation.get_frame() + 1) % 1);
    }

}

void Seagull::draw() {
    animation.draw_frame(get_position());
}

void Seagull::touch(const Object* from) {
    return;
}

void Seagull::die() {
    return;
}

void Seagull::hurt(int amount) {
    return;
}