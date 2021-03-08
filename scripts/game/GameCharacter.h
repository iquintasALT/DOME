#pragma once
#include "Entity.h"
#include "../components/MovementComponent.h"
class GameCharacter :
	public Entity
{
public:
	virtual void render() = 0;
};

