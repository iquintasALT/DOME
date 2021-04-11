#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../utils/checkML.h"
#include "../components/rigid_body.h"

class ClassicBullet : public Component {
private:
	Transform* tr_;
	Transform* playerTr;
	RigidBody* rb;
	int tier;

	void OnCollision(BoxCollider* collider) override;

public:
	ClassicBullet(Transform* player, int typeOfWeapon);

	virtual ~ClassicBullet();

	void init() override;
};
