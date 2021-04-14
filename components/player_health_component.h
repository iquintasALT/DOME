#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../sdlutils/Texture.h"

class PlayerHealthComponent : public Component
{
protected:
	Texture* t;
public:
	PlayerHealthComponent() : t(nullptr){};
	virtual ~PlayerHealthComponent() {};
	Texture* getTexture() { return t; }
};

