#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../game/checkML.h"

class PlayerHealthComponent : public Component
{
public:
	PlayerHealthComponent() {};
	virtual ~PlayerHealthComponent() {};
	virtual void init() {};
	virtual void update() {};
	virtual void render() {};
};

