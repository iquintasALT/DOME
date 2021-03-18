#pragma once
#include "../components/game_entity_component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

class GravityComponent : public GameEntityComponent {
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
