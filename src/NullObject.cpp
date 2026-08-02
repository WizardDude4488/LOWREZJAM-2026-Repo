#include <string>

#include "NullObject.hpp"

NullObject::NullObject(const std::string& n) {
    name = n;
    draw_layer = 0;
}

const std::string& NullObject::get_class() const {
    return "NullObject";
}

void NullObject::update(float dt) {
    return; // Do nothing
}

void NullObject::draw() {
    return; // Do nothing
}