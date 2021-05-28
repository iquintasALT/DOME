#pragma once
#include <cassert>
#include <list>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "transform.h"
#include "../utils/checkML.h"
#include "../components/rigid_body.h"
#include "../utils/ray_cast.h"

class Charge : public Component {
private:
	Transform* tr_;
	float angle;
	RayCast* raycast;
public:
	inline Charge(float angle, RayCast* rc) : tr_(nullptr), angle(angle), raycast(rc) {}

	inline virtual ~Charge() {}

	void init() override;

	virtual void update() override;

	void hitEnemies();
};

