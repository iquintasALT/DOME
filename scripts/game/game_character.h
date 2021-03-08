#pragma once
#include "Entity.h"
#include "../components/movement_component.h"
class GameCharacter :
	public Entity
{
public:
	virtual void render() = 0;
};

