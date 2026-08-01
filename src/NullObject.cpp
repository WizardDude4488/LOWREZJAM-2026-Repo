#include <string>

#include "NullObject.hpp"

NullObject::NullObject(const char* name) {
    this->name = std::string(name);
    this->draw_layer = 0;
}

void NullObject::update(const Game* g, float dt) {
    return; // Do nothing
}

void NullObject::draw(const Game* g) {
    return; // Do nothing
}