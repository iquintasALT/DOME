#pragma once
#include "game_entity_component.h"
#include "../game/checkML.h"

class PlayerHealthComponent : public GameEntityComponent
{
public:
	PlayerHealthComponent() {};
	virtual ~PlayerHealthComponent() {};
	virtual void init() {};
	virtual void update() {};
	virtual void render() {};
};

