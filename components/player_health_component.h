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
	PlayerHealthComponent() {};
	virtual ~PlayerHealthComponent() {};
	void setTexture(Texture* aux) { t = aux; }
	Texture* getTexture() { return t; }
};

