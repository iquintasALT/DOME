#pragma once
#include "game_object.h"
#include "physics_object.h"
class Entity :
	public GameObject,
	public PhysicsObject
{
public:
	virtual void render() = 0;
};

