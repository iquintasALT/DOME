#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

class PlayerHealthComponent : public Component
{
protected:
	Texture* t;
	int frameIndex;
public:
	PlayerHealthComponent() : t(&sdlutils().images().at("status_effects")){};
	virtual ~PlayerHealthComponent() {};
	inline int getFrameIndex() { return frameIndex; };
	Texture* getTexture() { return t; }
	
	short int renderPriority = 0;	// Higher priority -> further left

	bool operator<(const PlayerHealthComponent& other)const
	{
		return renderPriority < other.renderPriority;
	}
};
