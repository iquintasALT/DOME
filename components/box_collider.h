#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../utils/Collisions.h"
#include "../utils/checkML.h"

#include "Transform.h"

class RigidBody;

class BoxCollider : public Component
{
private:
	Transform* tr_;

	bool trigger;
public:
	inline BoxCollider(bool isTrigger = false) : tr_(nullptr), trigger(isTrigger) {};

	inline ~BoxCollider() {};

	virtual void init() override;

	inline bool isTrigger() { return trigger; };

	bool collision(Transform* ent, RigidBody* rb_);

	inline Transform* getTransform() { return tr_; };
};

