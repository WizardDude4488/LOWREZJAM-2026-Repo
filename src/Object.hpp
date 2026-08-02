#pragma once

#include <string>

//#include "Game.hpp" // use forward decl instead

class Game;

// Abstract class; cannot be directly instanced
class Object {
protected:
    int draw_layer = 0;
    std::string name;
public:
    virtual ~Object() = default;

    // Return draw_layer of this object
    int get_draw_layer() const;

    // Return name of this object
    const std::string& get_name() const;

    // Provide functions access to current game object
    //virtual void update(const Game* g, float dt) = 0; // Do away with passing g; access the game object by including Game.hpp
                                                        // and accessing current_game
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};