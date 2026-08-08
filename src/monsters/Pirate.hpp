#include "Character.hpp"

class Pirate : public Character {
protected:
	static const std::string class_name;

	float walk_speed = 10.0f;
	float target_radius;
	float state_time = 0.0f;
	float anim_time = 0.0f;

	Vector2 direction = { 0.0f, 0.0f };
	Vector2 velocity = { 0.0f, 0.0f };

	// TODO: add animation state
public:
	Pirate(const std::string& n, Vector2 pos, float radius);

	const std::string& get_class() const override;
	void update(float dt) override;
	void draw() override;

	void touch(const Object* from) override;

	void die() override;
	void hurt(int amount) override;

};