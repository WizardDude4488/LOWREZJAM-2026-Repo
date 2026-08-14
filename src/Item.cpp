#include <vector>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Helper.hpp"
#include "Animation.hpp"

#include "Item.hpp"
#include "Game.hpp"


void Item::touch(const Object* from) {
    if (from->get_class() == "Player") {
        //call base class deconstructor
        //make sure to remove any pointers to a deleted item from the objects list in main
        //update player inventory
        current_game->get_player_object()->add_item(this);
        delete this;
    } else {
        return;
    }
}

/*void Item::touch2() {
    delete this;
}
*/