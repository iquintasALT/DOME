#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../utils/Collisions.h"
#include "../game/checkML.h"

#include "Transform.h"

class BoxCollider : public Component
{
private:
	Transform* tr_;

public:
	inline BoxCollider() : tr_(nullptr) {};

	inline ~BoxCollider() {};

	virtual void init() override;

	void collision(Entity* ent);
};
