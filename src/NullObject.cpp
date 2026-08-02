#include <string>

#include "NullObject.hpp"

const std::string NullObject::class_name = "NullObject";

NullObject::NullObject(const std::string& n) {
    name = n;
    draw_layer = 0;
}

const std::string& NullObject::get_class() const {
    return class_name; // Do not do 'return "[string]";' this causes a runtime error
}

void NullObject::update(float dt) {
    return; // Do nothing
}

void NullObject::draw() {
    return; // Do nothing
}