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
        // DO NOT DO THIS:
        //delete this;
        // WHY: You gave a pointer to player, and then deleted the data that the pointer was pointing to.
        // This immediately invalidates the pointer, and trying to access the data there is data not given
        // to the process, causing the OS to stop the program.
    } else {
        return;
    }
}

/*void Item::touch2() {
    delete this;
}
*/