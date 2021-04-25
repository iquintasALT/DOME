#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../components/rigid_body.h"



class ClassicBullet : public Component {
private:
	Transform* tr_;
	RigidBody* rb_;

	void OnCollision(Entity* collider) override;

public:
	ClassicBullet();

	virtual ~ClassicBullet();

	void init() override;
};
