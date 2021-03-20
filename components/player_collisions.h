#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../game/checkML.h"

#include "Transform.h"
#include "tile_renderer.h"
#include "GravityComponent.h"


class PlayerCollisions : public Component
{
public:
	PlayerCollisions(Manager* mngr);

	~PlayerCollisions() {}

	virtual void init() override;

	virtual void update() override;

private:
	Transform* tr_;
	GravityComponent* gravity_;
	Manager* mngr_;
};

