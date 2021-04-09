#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"

class PlayerHealthComponent : public Component
{
public:
	PlayerHealthComponent() {};
	virtual ~PlayerHealthComponent() {};
};

