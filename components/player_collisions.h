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
public:
	PlayerCollisions(Manager* mngr, GravityComponent* gr);

	~PlayerCollisions() {}

	virtual void init() override;

	bool collisions(Vector2D& const newPos, int const w, int const h, Vector2D& vel);

private:
	GravityComponent* gravity_;
	Manager* mngr_;
};

