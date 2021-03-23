#pragma once
#include "../components/game_entity_component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

class GravityComponent : public GameEntityComponent {
public:
	GravityComponent(Transform* tr_) {
		gravity = consts::GRAVITY;
		entity_ = nullptr;
		entityTr = tr_;
		onFloor_ = false;
	};
	GravityComponent(){}

	virtual void update();

	void reachedFloor();

	bool onFloor() { return onFloor_; };

	void setOnFloor(const bool floor) { onFloor_ = floor; };

private:
	Transform* entityTr;
	float gravity;
	bool onFloor_;
};
