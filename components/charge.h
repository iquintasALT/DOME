#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "Transform.h"
#include "../game/checkML.h"

class Charge : public Component {
private:
	Transform* tr_;
	float angle;

public:
	inline Charge(float angle) : tr_(nullptr), angle(angle) {}

	inline virtual ~Charge() {}

	void init() override;

	virtual void update() override;
};

