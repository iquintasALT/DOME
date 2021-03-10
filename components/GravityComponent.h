#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../game/constant_variables.h"

class GravityComponent : public Component {
public:
	GravityComponent() {
		gravity = consts::GRAVITY;
		entity_ = nullptr;
	};

	virtual void init() {
		entityTr = entity_->getComponent<Transform>();
		assert(entityTr != nullptr);
	}

	virtual void update();
private:
	Transform* entityTr;
	float gravity;
};
