#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../game/checkML.h"

#include "tile_renderer.h"

class GravityComponent;

class PlayerCollisions : public Component
{
private:
	GravityComponent* gravity_;

public:
	PlayerCollisions();

	~PlayerCollisions() {}

	virtual void init() override;

	void update() override;
};

