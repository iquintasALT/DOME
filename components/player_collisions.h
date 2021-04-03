#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../game/checkML.h"

#include "tile_renderer.h"

class RigidBody;

class PlayerCollisions : public Component
{
private:
	RigidBody* rb_;

public:
	PlayerCollisions();

	~PlayerCollisions() {}

	virtual void init() override;

	void update() override;
};

