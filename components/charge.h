#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "Transform.h"
#include "../utils/checkML.h"

class Charge : public Component {
private:
	Transform* tr_;
	float angle;
	int damage;
public:
	inline Charge(float angle, int type) : tr_(nullptr), angle(angle) { damage = 75 * type; }

	inline virtual ~Charge() {}

	void init() override;

	virtual void update() override;
};

