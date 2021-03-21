#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "Transform.h"

class Charge : public Component {
public:
	Charge() : tr_(nullptr) {}

	virtual ~Charge() {}

	void init() override;

	virtual void update() override;

private:
	Transform* tr_;
};

