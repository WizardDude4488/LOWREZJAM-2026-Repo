#pragma once

#include <string>

#include "Entity.hpp"

class Bullet : public Entity {
protected:
	static const std::string& class_name;

	float speed;

	Vector2 direction;
	Vector2 velocity;
public:
	Bullet(const std::string& n, Vector2 pos, Vector2 dir, float s);

	// From Object
	const std::string& get_class() const override;

	void update(float dt) override;
	void draw() override;

	// From Entity
	void touch(const Object* from) override;
};