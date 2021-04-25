#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "Transform.h"
#include "../utils/checkML.h"
#include "../components/rigid_body.h"

class Charge : public Component {
private:
	Transform* tr_;
	float angle;
	RigidBody* rb;
	vector<Entity*> hitEnemies = {};
public:
	inline Charge(float angle) : tr_(nullptr), angle(angle) {}

	inline virtual ~Charge() {}

	void init() override;

	virtual void update() override;

	void OnCollision(Entity* collider) override;
};

