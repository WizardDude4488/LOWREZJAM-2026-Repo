#include <vector>
#include <string>
#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "Game.hpp"
#include "Helper.hpp"
#include "Weapon.hpp"
#include "RollingPin.hpp"

const std::string RollingPin::class_name = "RollingPin";

//const std::vector<int> RollingPin::attack_frames = {2, 1, 0};

const std::string& RollingPin::get_class() const {
    return class_name;
}

RollingPin::RollingPin(const std::string& n, int melee_dmg, Vector2 Pos) {
    name = n;
    draw_layer = 3;
    bounds = {Pos.x, Pos.y, 8, 8};
    animation = Animation("rolling-pin2", Helper::create_spritesheet_frames(8, 8, 24, 32, 12));
    melee_damage = melee_dmg; 
    
}

/*void RollingPin::use(const Object* from) override {
    if (from->get_class() == "Player") {
        //get objects list
        //iterate through list, check for objects of type crab, seagull, etc.
        //call pointer.hurt() based on weapon damage
        //else, do nothing
    }

}*/

void RollingPin::update(float dt) {
    if (held) {
        //std::cout << "\nUpdated weapon.";
        //update position and orientation
        Vector2 pos = {0, 0};
        //pos.x = player->get_position().x 
    
        //change animation frame based on last direction (implement later)
        if (IsKeyPressed(KEY_W)) { current_direction = UP;} //up
        if (IsKeyPressed(KEY_A)) { current_direction = LEFT;} //left
        if (IsKeyPressed(KEY_D)) { current_direction = RIGHT;} //right
        if (IsKeyPressed(KEY_S)) { current_direction = DOWN;} //down

        switch (current_direction) {
            case UP: //up
                //std::cout << "Facing Up." << std::endl;
                pos.x = (current_game->get_player_object())->get_position().x;
                pos.y = (current_game->get_player_object())->get_position().y - 5;
                draw_layer = 4;
                attack_frames = {8, 7, 6};
                break;
            case RIGHT: //right
                //std::cout << "Facing Right." << std::endl;
                pos.x = (current_game->get_player_object())->get_position().x + 5;
                pos.y = (current_game->get_player_object())->get_position().y - 1;
                draw_layer = 6; 
                attack_frames = {5, 4, 3};
                break;
            case DOWN:
                //std::cout << "Facing Down." << std::endl;
                pos.x = (current_game->get_player_object())->get_position().x;
                pos.y = (current_game->get_player_object())->get_position().y + 4;
                draw_layer = 6;
                attack_frames = {11, 10, 9};
                break;
            case LEFT:
                //std::cout << "Facing Left." << std::endl;
                pos.x = (current_game->get_player_object())->get_position().x - 8;
                pos.y = (current_game->get_player_object())->get_position().y - 1;
                draw_layer = 6; 
                attack_frames = {2, 1, 0};
                break;
            default: //default to right
                //std::cout << "Default." << std::endl;
                pos.x = (current_game->get_player_object())->get_position().x + 5;
                pos.y = (current_game->get_player_object())->get_position().y;
                draw_layer = 6; 
                attack_frames = {5, 4, 3};
                break;
        }

        set_position(pos);

        //handle attack buttons

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && current_state != ATTACKING) {
            std::vector<Object*> list = current_game->get_list();
            
            //setting state to attacking, setting animation frame to 0th index
            //0th index is 2nd frame
            //setting animation to 2nd frame
            current_state = ATTACKING;
            //animation_frame refers to the nth frame in the current animation (attack)
            //do not use animation frame for two different use cases at the same time
            animation_frame = 0;

            //checking for collision with enemies
            for (Object* i : list) {
                if (i->get_class() == "Crab" || i->get_class() == "Seagull") {
                    Entity* enemy = static_cast<Entity*>(i);
                    if (CheckCollisionRecs(bounds, enemy->get_bounds())) {
                        enemy->touch(this);
                    }
                }
            }
        }
        
        //incrementing animation time by dt, time between frames in seconds
        anim_time += dt;
        //forgot to use == instead of = to evaluate equivalency 
        if (current_state == ATTACKING) {
            //figure out a way for the frames to start at the end and work backwards
            while (anim_time >= 0.06 && animation_frame <= 2) {
                animation.set_frame(attack_frames.at(animation_frame));
                anim_time = 0;
                std::cout << attack_frames.at(animation_frame) << std::endl;
                animation_frame += 1;
                //it appears that the animation only plays for a single frame, if that, before ending
                //this is because the "playing weapon animation" text only prints a single time per click
                //this text should print three times per click
            }
            if (animation_frame >= 3) {
                current_state = READY;
                std::cout << "Idle animation." << std::endl;
                //this part of the code is being reached even when the player isn't attacking
            }
        } else {
            animation.set_frame(attack_frames.at(2));
        }
    } 
}

void RollingPin::draw() {
    animation.draw_frame(get_position());
}

void RollingPin::touch(const Object* from) {
    return;
}

//draw needs override
//touch needs override
//update needs override
//get_class() needs override