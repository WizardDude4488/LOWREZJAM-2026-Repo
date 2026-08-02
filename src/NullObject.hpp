#pragma once

#include <string>

#include "Object.hpp"

class NullObject : public Object {
public:
    NullObject(const std::string& n);
    const std::string& get_class() const override;

    ~NullObject() = default;

    void update(float dt) override;
    void draw() override;
};