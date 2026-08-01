#include "Object.hpp"

int Object::get_draw_layer() const {
    return draw_layer;
}

const std::string& Object::get_name() const {
    return name;
}