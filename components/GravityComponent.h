#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

#include "rigid_body.h"

class RigidBody : public Component {
private:
	float gravity;
	bool onFloor_;

public:
	RigidBody();

	inline ~RigidBody() {};

	virtual void init() override;

	virtual void applyGravity();

	void reachedFloor();

	inline bool onFloor() { return onFloor_; };

	inline void setOnFloor(const bool floor) { onFloor_ = floor; };
};
