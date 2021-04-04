// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../game/checkML.h"


class Ricochet : public Component {
private:
	Transform* tr_;
	Transform* playerTr;
	int n; //numero rebotes
	int tier;

public:
	Ricochet(Transform* player, int nrebotes, int typeOfWeapon);

	virtual ~Ricochet();

	void init() override;

	void createExplosion();

	void update() override;
};
