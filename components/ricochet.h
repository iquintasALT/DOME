// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class Ricochet : public Component {
public:
	Ricochet(): tr_(nullptr), n(4) {}

	virtual ~Ricochet() {}

	void init() override;

	void update() override;

private:
	Transform* tr_;
	int n; //numero rebotes
};
