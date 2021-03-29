#pragma once
#include "../components/game_entity_component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

class GravityComponent : public GameEntityComponent {
private:
	Transform* entityTr;
	float gravity;
	bool onFloor_;

public:
	GravityComponent();

	inline ~GravityComponent() {};

	virtual void init() override;

	virtual void update();

	void reachedFloor();

	inline bool onFloor() { return onFloor_; };

	inline void setOnFloor(const bool floor) { onFloor_ = floor; };
};
