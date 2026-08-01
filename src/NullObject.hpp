#pragma once

#include "Object.hpp"

class NullObject : public Object {
public:
    NullObject(const char* name);
    ~NullObject() = default;

    void update(const Game* g, float dt) override;
    void draw(const Game* g) override;
};