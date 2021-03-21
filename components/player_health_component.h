#pragma once
#include "game_entity_component.h"
class PlayerHealthComponent : public GameEntityComponent
{
public:
	PlayerHealthComponent() {};
	virtual ~PlayerHealthComponent() {};
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

